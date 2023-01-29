#pragma once
#include <llapi/LLAPI.h>
#include <llapi/perm/Role.hpp>

#if defined(PERMAPI_EXPORTS)
#define PERMAPI _declspec(dllexport)
#else
#define PERMAPI _declspec(dllimport)
#endif

class PermissionAPI {

public:

    /**
     * @brief Create a Role object.
     *
     * @param  name         The name of the role.
     * @param  displayName  The display name of the role.
     * @return std::weak_ptr<ll::perm::Role>  The created role(weak ref).
     * @throws std::invalid_argument      If the role already exists.
     * @par Example
     * @code
     * PermissionAPI api;
     * auto role = api.createRole("role1", "Role 1");
     * ...
     * if (!role.expired()) {
     *     auto rolePtr = role.lock();
     *     rolePtr->addMember("1145141919810");
     *     api.saveData();
     * }
     * @endcode
     */
    static PERMAPI std::weak_ptr<ll::perm::Role> createRole(const std::string& name, const std::string& displayName);

    /**
     * @brief Check if a role exists.
     *
     * @param  name  The name of the role.
     * @return bool  True If the role exists, false otherwise.
     */
    static PERMAPI bool roleExists(const std::string& name);

    /**
     * @brief Get a role object.
     *
     * @param  name                       The name of the role.
     * @return std::weak_ptr<ll::perm::Role>  The role(weak ref).
     * @throws std::invalid_argument      If the role does not exist.
     */
    static PERMAPI std::weak_ptr<ll::perm::Role> getRole(const std::string& name);

    /**
     * @brief Get a role object. If the role does not exist, it will be created.
     *
     * @param  name                       The name of the role.
     * @return std::weak_ptr<ll::perm::Role>  The role(weak ref).
     */
    static PERMAPI std::weak_ptr<ll::perm::Role> getOrCreateRole(const std::string& name);

    /**
     * @brief Delete a role.
     *
     * @param  name  The name of the role.
     * @throws std::invalid_argument  If the role not found.
     */
    static PERMAPI void deleteRole(const std::string& name);

    /**
     * @brief Register an permission.
     *
     * @param name  The name of the permission.
     * @param desc  The description name of the permission.
     */
    static PERMAPI void registerPermission(const std::string& name, const std::string& desc);

    /**
     * @brief Delete a permission.
     *
     * @param    name  The name of the permission.
     * @warning  This function will also delete the permission instances in roles.
     */
    static PERMAPI void deletePermission(const std::string& name);

    /**
     * @brief Check if a permission exists.
     *
     * @param  name  The name of the permission.
     * @return bool  True If the permission exists, false otherwise.
     */
    static PERMAPI bool permissionExists(const std::string& name);

    /**
     * @brief Check whether the player has the Permission or not.
     *
     * @param  xuid  The xuid of the player.
     * @param  name  The name of the Permission.
     * @return bool  True If the player has the Permission, false otherwise.
     */
    static PERMAPI bool checkPermission(const xuid_t& xuid, const std::string& name);

    /**
     * @brief Check if a player is a member of a role.
     *
     * @param  xuid  The xuid of the player.
     * @param  name  The name of the role.
     * @return bool  True If the player is a member of the role, false otherwise.
     */
    static PERMAPI bool isMemberOf(const xuid_t& xuid, const std::string& name);

    /**
     * @brief Get the roles of a player.
     *
     * @param  xuid         The xuid of the player.
     * @return ll::perm::Roles  The roles of the player.
     */
    static PERMAPI ll::perm::Roles getPlayerRoles(const xuid_t& xuid);

    /**
     * @brief Get the permissions of a player.
     *
     * @param  xuid               The xuid of the player.
     * @return ll::perm::Permissions  The permissions of the player.
     */
    static PERMAPI ll::perm::Permissions getPlayerPermissions(const xuid_t& xuid);

    /**
     * @brief Save the data.
     */
    static PERMAPI void saveData();
};
