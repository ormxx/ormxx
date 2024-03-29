#ifndef ORMXX_ORMXX_H
#define ORMXX_ORMXX_H

#include <cstddef>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "./internal/defer.h"
#include "./internal/field_builder.h"
#include "./sql/generate_create_table_sql.h"
#include "./sql/generate_delete_sql_statement.h"
#include "./sql/generate_drop_table_sql.h"
#include "./sql/generate_insert_sql_statement.h"
#include "./sql/generate_select_sql_statement.h"
#include "./sql/generate_update_sql_statement.h"
#include "./sql/sql_expr.h"
#include "./sql/sql_utility.h"
#include "./types_check/is_field_builder.h"

#include "./interface/index.h"            // IWYU pragma: export
#include "./internal/inject_utility.h"    // IWYU pragma: export
#include "./internal/macros.h"            // IWYU pragma: export
#include "./internal/result_to_entity.h"  // IWYU pragma: export
#include "./options/index.h"              // IWYU pragma: export

namespace ormxx {

class ORMXX {
public:
    using ConnectionType = Adaptor::ConnectionType;

public:
    struct Options {
        size_t max_idle_connection{128};
    };

    class Builder {
    public:
        Builder() = delete;
        Builder(Adaptor* adaptor) : adaptor_(adaptor) {}

        Builder& WithMaxIdleConnection(size_t max_idle_connection) {
            options_.max_idle_connection = max_idle_connection;
            return *this;
        }

        ORMXX Build() {
            return ORMXX(adaptor_, options_);
        }

        ORMXX* BuildPtr() {
            return new ORMXX(adaptor_, options_);
        }

    private:
        Adaptor* adaptor_;
        Options options_;
    };

public:
    template <typename Struct>
    class QueryBuilder {
    public:
        QueryBuilder(ORMXX& ormxx) : ormxx_(ormxx) {
            if constexpr (!std::is_void_v<Struct>) {
                const auto table_options_ = internal::InjectEntrance::GetTableOptions<Struct>();
                sql_expr_.sql_from.SetSQLString(fmt::format("`{}`", table_options_.table_name));
            }
        }

        virtual ~QueryBuilder() = default;

    public:
        const auto& NewFields() {
            return internal::InjectEntrance::GetFieldBuilder<Struct>();
        }

    public:
        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& And(T* t) {
            std::string prefix = sql_expr_.sql_where.Empty() ? "" : " AND ";

            auto w = internal::SQLUtility::GenerateWhereSQLStatement(t);
            sql_expr_.sql_where.AppendSQLString(fmt::format("{}({})", prefix, w.GetSQLString()));
            sql_expr_.sql_where.AppendFields(w.GetFields());

            return *this;
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& And(T&& t) {
            return And(&t);
        }

        template <typename... FieldBuilder,
                  std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
        QueryBuilder& And(FieldBuilder&&... fb) {
            std::string prefix = sql_expr_.sql_where.Empty() ? "" : " AND ";

            auto w = internal::SQLUtility::GenerateWhereSQLStatement(std::forward<FieldBuilder>(fb)...);
            sql_expr_.sql_where.AppendSQLString(fmt::format("{}({})", prefix, w.GetSQLString()));
            sql_expr_.sql_where.AppendFields(w.GetFields());

            return *this;
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& Or(T* t) {
            std::string prefix = sql_expr_.sql_where.Empty() ? "" : " OR ";

            auto w = internal::SQLUtility::GenerateWhereSQLStatement(t);
            sql_expr_.sql_where.AppendSQLString(fmt::format("{}({})", prefix, w.GetSQLString()));
            sql_expr_.sql_where.AppendFields(w.GetFields());

            return *this;
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& Or(T&& t) {
            return Or(&t);
        }

        template <typename... FieldBuilder,
                  std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
        QueryBuilder& Or(FieldBuilder&&... c) {
            std::string prefix = sql_expr_.sql_where.Empty() ? "" : " OR ";

            auto w = internal::SQLUtility::GenerateWhereSQLStatement(std::forward<FieldBuilder>(c)...);
            sql_expr_.sql_where.AppendSQLString(fmt::format("{}({})", prefix, w.GetSQLString()));
            sql_expr_.sql_where.AppendFields(w.GetFields());

            return *this;
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& Where(T* t) {
            return And(t);
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        QueryBuilder& Where(T&& t) {
            return Where(&t);
        }

        template <typename... FieldBuilder,
                  std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
        QueryBuilder& Where(FieldBuilder&&... c) {
            return And(std::forward<FieldBuilder>(c)...);
        }

        template <typename... FieldBuilder,
                  std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
        QueryBuilder& Order(FieldBuilder&&... c) {
            sql_expr_.sql_order = internal::SQLUtility::GenerateOrderSQLStatement(std::forward<FieldBuilder>(c)...);
            return *this;
        }

        QueryBuilder& Limit(uint64_t limit = 1) {
            sql_expr_.sql_limit = fmt::format("{}", limit);
            return *this;
        }

        QueryBuilder& Offset(uint64_t offset = 1) {
            sql_expr_.sql_offset = fmt::format("{}", offset);
            return *this;
        }

        template <std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<Struct>>, bool> = true>
        ResultOr<Struct> First() {
            Struct s{};

            auto _sql_data = sql_expr_;
            _sql_data.sql_select = internal::SQLUtility::GenerateAllFieldNameSelectSQLString(&s);
            _sql_data.sql_limit.SetSQLString("1");

            RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateSelectSQLStatement(_sql_data));
            RESULT_VALUE_OR_RETURN(auto execute_res, ormxx_.ExecuteQuery(sql_statement));

            RESULT_OK_OR_RETURN(internal::ResultToEntity(*execute_res, s));

            return s;
        }

        template <std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<Struct>>, bool> = true>
        ResultOr<std::vector<Struct>> Find() {
            Struct s{};

            auto _sql_data = sql_expr_;
            _sql_data.sql_select = internal::SQLUtility::GenerateAllFieldNameSelectSQLString(&s);

            RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateSelectSQLStatement(_sql_data));
            RESULT_VALUE_OR_RETURN(auto execute_res, ormxx_.ExecuteQuery(sql_statement));

            std::vector<Struct> s_vec;
            RESULT_OK_OR_RETURN(internal::ResultToEntity(*execute_res, s_vec));

            return s_vec;
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        ResultOr<std::unique_ptr<ExecuteResult>> Update(T* t) {
            RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateUpdateSQLStatement(sql_expr_, *t));
            RESULT_DIRECT_RETURN(ormxx_.ExecuteUpdate(sql_statement));
        }

        template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
        ResultOr<std::unique_ptr<ExecuteResult>> Update(T t) {
            return Update(&t);
        }

        template <typename... FieldBuilder,
                  std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
        ResultOr<std::unique_ptr<ExecuteResult>> Update(FieldBuilder&&... field_builder) {
            RESULT_VALUE_OR_RETURN(
                    const auto sql_statement,
                    GenerateUpdateSQLStatement<Struct>(sql_expr_, std::forward<FieldBuilder>(field_builder)...));
            RESULT_DIRECT_RETURN(ormxx_.ExecuteUpdate(sql_statement));
        }

        ResultOr<std::unique_ptr<ExecuteResult>> Delete() {
            RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateDeleteSQLStatement<Struct>(sql_expr_));
            RESULT_DIRECT_RETURN(ormxx_.ExecuteUpdate(sql_statement));
        }

    private:
        internal::SQLExpr sql_expr_{};
        ORMXX& ormxx_;
    };

public:
    template <typename T>
    QueryBuilder<T> NewQueryBuilder() {
        return QueryBuilder<T>(*this);
    }

    template <typename T>
    const auto& NewFields() {
        return internal::InjectEntrance::GetFieldBuilder<T>();
    }

protected:
    struct connectionPoolNode {
        std::mutex mutex_;
        std::list<Connection*> pool;
    };

public:
    ORMXX() {}

    ORMXX(Adaptor* adaptor, const Options& options) : adaptor_(adaptor), options_(options) {}

    virtual ~ORMXX() {
        for (auto& [k, v] : connection_pool_node_map_) {
            while (!v.pool.empty()) {
                auto* connection = v.pool.front();
                v.pool.pop_front();

                connection->Close();
                delete connection;
            }
        }

        if (adaptor_) {
            delete adaptor_;
        }
    }

public:
    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const SQLStatement& sql_statement) {
#if defined(ORMXX_BUILD_TESTS)
        addSQLStatementToHistory(sql_statement);
#endif

        if (conn_ != nullptr) {
            RESULT_DIRECT_RETURN(conn_->Execute(sql_statement));
        }

        RESULT_VALUE_OR_RETURN(auto* conn, getWriteConnection());
        __ORMXX_DEFER([&conn, this]() {
            releaseWriteConnection(conn);
        });

        RESULT_DIRECT_RETURN(conn->Execute(sql_statement));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(Execute(sql_statement));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const SQLStatement& sql_statement) {
#if defined(ORMXX_BUILD_TESTS)
        addSQLStatementToHistory(sql_statement);
#endif

        if (conn_ != nullptr) {
            RESULT_DIRECT_RETURN(conn_->ExecuteQuery(sql_statement));
        }

        RESULT_VALUE_OR_RETURN(auto* conn, getReadConnection());
        __ORMXX_DEFER([&conn, this]() {
            releaseReadConnection(conn);
        });

        RESULT_DIRECT_RETURN(conn->ExecuteQuery(sql_statement));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(ExecuteQuery(sql_statement));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const SQLStatement& sql_statement) {
#if defined(ORMXX_BUILD_TESTS)
        addSQLStatementToHistory(sql_statement);
#endif

        if (conn_ != nullptr) {
            RESULT_DIRECT_RETURN(conn_->ExecuteUpdate(sql_statement));
        }

        RESULT_VALUE_OR_RETURN(auto* conn, getWriteConnection());
        __ORMXX_DEFER([&conn, this]() {
            releaseWriteConnection(conn);
        });

        RESULT_DIRECT_RETURN(conn->ExecuteUpdate(sql_statement));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql_statement));
    }

public:
    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    Result CheckSchema() {
        RESULT_DIRECT_RETURN(GenerateCreateTableSQL<T>());
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> DropTable() {
        RESULT_VALUE_OR_RETURN(const auto sql, GenerateDropTableSQL<T>());
        RESULT_DIRECT_RETURN(Execute(sql));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> CreateTable() {
        RESULT_VALUE_OR_RETURN(const auto sql, GenerateCreateTableSQL<T>());
        RESULT_DIRECT_RETURN(Execute(sql));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T* t) {
        RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateInsertSQLStatement<T>(t));
        RESULT_VALUE_OR_RETURN(auto execute_res, ExecuteUpdate(sql_statement));

        if constexpr (!std::is_const_v<T>) {
            internal::InjectUtility::ClearIsSetMap(t);
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(std::vector<T>* t) {
        RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateInsertSQLStatement<T>(t));
        RESULT_VALUE_OR_RETURN(auto execute_res, ExecuteUpdate(sql_statement));

        for (auto& _t : *t) {
            internal::InjectUtility::ClearIsSetMap(&_t);
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(const std::vector<T>* t) {
        RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateInsertSQLStatement<T>(t));
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql_statement));
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T t) {
        RESULT_DIRECT_RETURN(Insert(&t));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T* t) {
        RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateDeleteSQLStatement<T>(t));
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql_statement));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T t) {
        RESULT_DIRECT_RETURN(Delete(&t));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Update(T* t) {
        RESULT_VALUE_OR_RETURN(const auto sql_statement, GenerateUpdateSQLStatement<T>(t));
        RESULT_VALUE_OR_RETURN(auto execute_res, ExecuteUpdate(sql_statement));

        if constexpr (!std::is_const_v<T>) {
            internal::InjectUtility::ClearIsSetMap(t);
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Update(T t) {
        RESULT_DIRECT_RETURN(Update(&t));
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<T> First() {
        RESULT_DIRECT_RETURN(NewQueryBuilder<T>().First());
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    Result First(T* t) {
        RESULT_VALUE_OR_RETURN(*t, First<T>());
        return Result::OK();
    }

    template <typename Func>
    Result Transaction(Func func) {
        RESULT_VALUE_OR_RETURN(auto* conn, getWriteConnection());
        __ORMXX_DEFER([&conn, this]() {
            releaseWriteConnection(conn);
        });

        conn_ = conn;

        RESULT_OK_OR_RETURN(conn_->BeginTransaction());

        auto res = func();
        if (!res.IsOK()) {
            conn_->Rollback();
            RESULT_DIRECT_RETURN(res);
        }

        RESULT_DIRECT_RETURN(conn_->Commit());
    }

private:
    ResultOr<Connection*> getConnection(ConnectionType connection_type = ConnectionType::WRITE) {
        if (adaptor_ == nullptr) {
            auto res = Result::Builder(Result::ErrorCode::NotInitializedError).Build();
            RESULT_DIRECT_RETURN(res);
        }

        auto& node = connection_pool_node_map_[connection_type];
        std::unique_lock<std::mutex> lock(node.mutex_);

        while (!node.pool.empty()) {
            auto* connection = node.pool.front();
            node.pool.pop_front();
            if (connection->ReConnect()) {
                return connection;
            } else {
                releaseConn(connection);
            }
        }

        RESULT_DIRECT_RETURN(adaptor_->GetConnection(connection_type));
    }

    ResultOr<Connection*> getWriteConnection() {
        return getConnection(ConnectionType::WRITE);
    }

    ResultOr<Connection*> getReadConnection() {
        return getConnection(ConnectionType::READ);
    }

    void releaseConnection(Connection* connection, ConnectionType connection_type = ConnectionType::WRITE) {
        auto& node = connection_pool_node_map_[connection_type];
        std::unique_lock<std::mutex> lock(node.mutex_);

        if (node.pool.size() < options_.max_idle_connection) {
            node.pool.push_back(connection);
        } else {
            releaseConn(connection);
        }
    }

    void releaseWriteConnection(Connection* connection) {
        releaseConnection(connection, ConnectionType::WRITE);
    }

    void releaseReadConnection(Connection* connection) {
        releaseConnection(connection, ConnectionType::READ);
    }

protected:
    void releaseConn(Connection* connection) {
        connection->Close();
        delete connection;
    }

protected:
    std::unordered_map<ConnectionType, connectionPoolNode> connection_pool_node_map_{};

    Adaptor* adaptor_{nullptr};

    Options options_{};

    inline static thread_local Connection* conn_ = nullptr;

#if defined(ORMXX_BUILD_TESTS)
private:
    void addSQLStatementToHistory(const SQLStatement& sql_statement) {
        sql_statement_history_.push_back(sql_statement);
    }

    const std::vector<SQLStatement>& getSQLStatementHistory() const {
        return sql_statement_history_;
    }

    const SQLStatement& getLastSQLStatement() const {
        return sql_statement_history_.back();
    }

    std::vector<SQLStatement> sql_statement_history_{};
#endif
};

}  // namespace ormxx

#endif  // ORMXX_ORMXX_H
