#pragma once
#include <llapi/perm/Role.hpp>

template <typename T>
void from_json(const nlohmann::json& j, ll::perm::PermVector<T>& v);
template <typename T>
void to_json(nlohmann::json& j, const ll::perm::PermVector<T>& v);

template <typename T>
void from_json(const nlohmann::json& j, ll::perm::PermContainer<T>& v);
template <typename T>
void to_json(nlohmann::json& j, const ll::perm::PermContainer<T>& v);

void from_json(const nlohmann::json& j, ll::perm::PermInstance& v);
void to_json(nlohmann::json& j, const ll::perm::PermInstance& v);

void from_json(const nlohmann::json& j, ll::perm::Permissions& v);
void to_json(nlohmann::json& j, const ll::perm::Permissions& v);

void from_json(const nlohmann::json& j, ll::perm::PermInfoList& v);
void to_json(nlohmann::json& j, const ll::perm::PermInfoList& v);

void from_json(const nlohmann::json& j, ll::perm::GeneralRole& v);
void to_json(nlohmann::json& j, const ll::perm::GeneralRole& v);

void from_json(const nlohmann::json& j, ll::perm::EveryoneRole& v);
void to_json(nlohmann::json& j, const ll::perm::EveryoneRole& v);

void from_json(const nlohmann::json& j, ll::perm::AdminRole& v);
void to_json(nlohmann::json& j, const ll::perm::AdminRole& v);

void from_json(const nlohmann::json& j, ll::perm::Roles& v);
void to_json(nlohmann::json& j, const ll::perm::Roles& v);



// PermVector<T>
template <typename T>
inline void from_json(const nlohmann::json& j, ll::perm::PermVector<T>& v) {
    v = j.get<std::vector<T>>();
}
template <typename T>
inline void to_json(nlohmann::json& j, const ll::perm::PermVector<T>& v) {
    j = (std::vector<T>)v;
}

// PermContainer<T>
template <typename T>
inline void from_json(const nlohmann::json& j, ll::perm::PermContainer<T>& v) {
    v = j.get<std::vector<T>>();
}
template <typename T>
inline void to_json(nlohmann::json& j, const ll::perm::PermContainer<T>& v) {
    j = (std::vector<T>)v;
}

// PermInstance
inline void from_json(const nlohmann::json& j, ll::perm::PermInstance& v) {
    if (j.is_boolean()) {
        v.enabled = j.get<bool>();
        return;
    }
    if (j.contains("enabled")) {
        v.enabled = j["enabled"];
        auto copy = j;
        copy.erase("enabled");
        v.extra = copy;
    } else {
        throw std::runtime_error("Failed to load the permission instance: the json object does not contain the 'enabled' field");
    }
}
inline void to_json(nlohmann::json& j, const ll::perm::PermInstance& v) {
    if (!v.extra.is_object() || (v.extra.is_object() && v.extra.empty())) {
        j = v.enabled;
        return;
    }
    j["enabled"] = v.enabled;
    if (v.extra.is_object() && !v.extra.empty()) {
        j.merge_patch(v.extra);
    }
}

// Permissions
inline void from_json(const nlohmann::json& j, ll::perm::Permissions& v) {
    v.clear();
    for (auto it = j.begin(); it != j.end(); ++it) {
        ll::perm::PermInstance a;
        from_json(it.value(), a);
        a.name = it.key();
        v.push_back(a);
    }
}
inline void to_json(nlohmann::json& j, const ll::perm::Permissions& v) {
    j = nlohmann::json::object();
    for (auto& it : v) {
        to_json(j[it.name], it);
    }
}

// PermInfoList
inline void from_json(const nlohmann::json& j, ll::perm::PermInfoList& v) {
    v.clear();
    for (auto it = j.begin(); it != j.end(); ++it) {
        ll::perm::PermInfo info;
        info.name = it.key();
        info.desc = it.value()["desc"];
    }
}
inline void to_json(nlohmann::json& j, const ll::perm::PermInfoList& v) {
    j = nlohmann::json::object();
    for (auto& it : v) {
        j[it.name] = {
            {"desc", it.desc}
        };
    }
}

// GeneralRole
inline void from_json(const nlohmann::json& j, ll::perm::GeneralRole& v) {
    if (j.contains("members")) v.getMembers() = j["members"].get<ll::perm::Members>();
    if (j.contains("priority")) v.priority = j["priority"];
    if (j.contains("displayName")) v.displayName = j["displayName"];
    if (j.contains("permissions")) from_json(j["permissions"], v.getPermissions());
}

inline void to_json(nlohmann::json& j, const ll::perm::GeneralRole& v) {
    j["members"] = v.getMembers();
    j["priority"] = v.priority;
    j["displayName"] = v.displayName;
    to_json(j["permissions"], v.getPermissions());
}

// EveryoneRole
inline void from_json(const nlohmann::json& j, ll::perm::EveryoneRole& v) {
    if (j.contains("priority")) v.priority = j["priority"];
    if (j.contains("displayName")) v.displayName = j["displayName"];
    if (j.contains("permissions")) from_json(j["permissions"], v.getPermissions());
}
inline void to_json(nlohmann::json& j, const ll::perm::EveryoneRole& v) {
    j["priority"] = v.priority;
    j["displayName"] = v.displayName;
    to_json(j["permissions"], v.getPermissions());
}

// AdminRole
inline void from_json(const nlohmann::json& j, ll::perm::AdminRole& v) {
    if (j.contains("members")) v.getMembers() = j["members"].get<ll::perm::Members>();
    if (j.contains("priority")) v.priority = j["priority"];
    if (j.contains("displayName")) v.displayName = j["displayName"];
    if (j.contains("permissions")) from_json(j["permissions"], v.getPermissions());
}

inline void to_json(nlohmann::json& j, const ll::perm::AdminRole& v) {
    j["members"] = v.getMembers();
    j["priority"] = v.priority;
    j["displayName"] = v.displayName;
    to_json(j["permissions"], v.getPermissions());
}

// Roles
inline void from_json(const nlohmann::json& j, ll::perm::Roles& v) {
    v.clear();
    for (auto it = j.begin(); it != j.end(); ++it) {
        auto& name = it.key();
        if (name == "everyone") {
            ll::perm::EveryoneRole role;
            from_json(it.value(), role);
            role.name = name;
            v.push_back(std::make_shared<ll::perm::EveryoneRole>(role));
        } else if (name == "admin") {
            ll::perm::AdminRole role;
            from_json(it.value(), role);
            role.name = name;
            v.push_back(std::make_shared<ll::perm::AdminRole>(role));
        } else {
            ll::perm::GeneralRole role;
            from_json(it.value(), role);
            role.name = name;
            v.push_back(std::make_shared<ll::perm::GeneralRole>(role));
        }
        if (v.back()->name.empty()) {
            throw std::runtime_error("Failed to load the perm role: the name of the role is empty!");
        }
        if (v.back()->displayName.empty()) {
            v.back()->displayName = name;
        }
    }
}
inline void to_json(nlohmann::json& j, const ll::perm::Roles& v) {
    for (auto& it : v) {
        switch (it->getType()) {
            case ll::perm::Role::Type::General:
                to_json(j[it->name], *(ll::perm::GeneralRole*)it.get());
                break;
            case ll::perm::Role::Type::Admin:
                to_json(j[it->name], *(ll::perm::AdminRole*)it.get());
                break;
            case ll::perm::Role::Type::Everyone:
                to_json(j[it->name], *(ll::perm::EveryoneRole*)it.get());
                break;
            default:
                break;
        }
    }
}
