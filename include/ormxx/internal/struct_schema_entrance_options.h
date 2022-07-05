#ifndef ORMXX_INTERNAL_STRUCT_SCHEMA_ENTRANCE_OPTIONS_H
#define ORMXX_INTERNAL_STRUCT_SCHEMA_ENTRANCE_OPTIONS_H

#include <cstddef>

namespace ormxx::internal {

struct StructSchemaEntranceOptions {
    bool visit_field{false};
    bool visit_key{false};
    bool visit_for_each{false};
    bool visit_field_by_index{false};
    bool visit_field_by_name{false};
    size_t index{0};
    const char* name{nullptr};
};

class StructSchemaEntranceOptionsBuilder {
public:
    StructSchemaEntranceOptionsBuilder() {}

    StructSchemaEntranceOptionsBuilder& WithVisitField(bool visit_field = true) {
        options_.visit_field = visit_field;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitKey(bool visit_key = true) {
        options_.visit_key = visit_key;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitForEach(bool visit_for_each = true) {
        options_.visit_for_each = visit_for_each;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitFieldByIndex(bool visit_field_by_index = true) {
        options_.visit_field_by_index = visit_field_by_index;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitFieldByName(bool visit_field_by_name = true) {
        options_.visit_field_by_name = visit_field_by_name;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithIndex(size_t index) {
        options_.index = index;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithName(const char* name) {
        options_.name = name;
        return *this;
    }

    StructSchemaEntranceOptions Build() {
        return options_;
    }

private:
    StructSchemaEntranceOptions options_;
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_STRUCT_SCHEMA_ENTRANCE_OPTIONS_H
