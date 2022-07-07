#ifndef ORMXX_INTERNAL_STRUCT_SCHEMA_ENTRANCE_OPTIONS_H
#define ORMXX_INTERNAL_STRUCT_SCHEMA_ENTRANCE_OPTIONS_H

#include <cstddef>

#include "../options/key_options.h"

namespace ormxx::internal {

struct StructSchemaEntranceOptions {
    bool visit_field{false};
    bool visit_key{false};
    bool visit_for_each{false};
    bool visit_field_by_index{false};
    bool visit_field_by_name{false};
    bool visit_field_by_is_set{false};
    bool visit_key_by_key_type{false};

    size_t index{0};
    std::string name{""};
    KeyOptions::KeyType key_type{KeyOptions::KeyType::PRIMARY};
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

    StructSchemaEntranceOptionsBuilder& WithVisitFieldByIsSet(bool visit_field_by_is_set = true) {
        options_.visit_field_by_is_set = visit_field_by_is_set;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitFieldByIndex(size_t index) {
        options_.visit_field_by_index = true;
        options_.index = index;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitFieldByName(const std::string& name) {
        options_.visit_field_by_name = true;
        options_.name = name;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithVisitKeyByKeyType(KeyOptions::KeyType key_type) {
        options_.visit_key_by_key_type = true;
        options_.key_type = key_type;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithIndex(size_t index) {
        options_.index = index;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithName(const std::string& name) {
        options_.name = name;
        return *this;
    }

    StructSchemaEntranceOptionsBuilder& WithKeyType(KeyOptions::KeyType key_type) {
        options_.key_type = key_type;
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
