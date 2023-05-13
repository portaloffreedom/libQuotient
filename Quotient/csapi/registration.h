/******************************************************************************
 * THIS FILE IS GENERATED - ANY EDITS WILL BE OVERWRITTEN
 */

#pragma once

#include <Quotient/csapi/definitions/auth_data.h>
#include <Quotient/csapi/definitions/request_email_validation.h>
#include <Quotient/csapi/definitions/request_msisdn_validation.h>
#include <Quotient/csapi/definitions/request_token_response.h>
#include <Quotient/jobs/basejob.h>

namespace Quotient {

/*! \brief Register for an account on this homeserver.
 *
 * This API endpoint uses the [User-Interactive Authentication
 * API](/client-server-api/#user-interactive-authentication-api), except in the
 * cases where a guest account is being registered.
 *
 * Register for an account on this homeserver.
 *
 * There are two kinds of user account:
 *
 * - `user` accounts. These accounts may use the full API described in this
 * specification.
 *
 * - `guest` accounts. These accounts may have limited permissions and may not
 * be supported by all servers.
 *
 * If registration is successful, this endpoint will issue an access token
 * the client can use to authorize itself in subsequent requests.
 *
 * If the client does not supply a `device_id`, the server must
 * auto-generate one.
 *
 * The server SHOULD register an account with a User ID based on the
 * `username` provided, if any. Note that the grammar of Matrix User ID
 * localparts is restricted, so the server MUST either map the provided
 * `username` onto a `user_id` in a logical manner, or reject
 * `username`\s which do not comply to the grammar, with
 * `M_INVALID_USERNAME`.
 *
 * Matrix clients MUST NOT assume that localpart of the registered
 * `user_id` matches the provided `username`.
 *
 * The returned access token must be associated with the `device_id`
 * supplied by the client or generated by the server. The server may
 * invalidate any access token previously associated with that device. See
 * [Relationship between access tokens and
 * devices](/client-server-api/#relationship-between-access-tokens-and-devices).
 *
 * When registering a guest account, all parameters in the request body
 * with the exception of `initial_device_display_name` MUST BE ignored
 * by the server. The server MUST pick a `device_id` for the account
 * regardless of input.
 *
 * Any user ID returned by this API must conform to the grammar given in the
 * [Matrix specification](/appendices/#user-identifiers).
 */
class QUOTIENT_API RegisterJob : public BaseJob {
public:
    /*! \brief Register for an account on this homeserver.
     *
     * \param kind
     *   The kind of account to register. Defaults to `user`.
     *
     * \param auth
     *   Additional authentication information for the
     *   user-interactive authentication API. Note that this
     *   information is *not* used to define how the registered user
     *   should be authenticated, but is instead used to
     *   authenticate the `register` call itself.
     *
     * \param username
     *   The basis for the localpart of the desired Matrix ID. If omitted,
     *   the homeserver MUST generate a Matrix ID local part.
     *
     * \param password
     *   The desired password for the account.
     *
     * \param deviceId
     *   ID of the client device. If this does not correspond to a
     *   known client device, a new device will be created. The server
     *   will auto-generate a device_id if this is not specified.
     *
     * \param initialDeviceDisplayName
     *   A display name to assign to the newly-created device. Ignored
     *   if `device_id` corresponds to a known device.
     *
     * \param inhibitLogin
     *   If true, an `access_token` and `device_id` should not be
     *   returned from this call, therefore preventing an automatic
     *   login. Defaults to false.
     *
     * \param refreshToken
     *   If true, the client supports refresh tokens.
     */
    explicit RegisterJob(const QString& kind = QStringLiteral("user"),
                         const Omittable<AuthenticationData>& auth = none,
                         const QString& username = {},
                         const QString& password = {},
                         const QString& deviceId = {},
                         const QString& initialDeviceDisplayName = {},
                         Omittable<bool> inhibitLogin = none,
                         Omittable<bool> refreshToken = none);

    // Result properties

    /// The fully-qualified Matrix user ID (MXID) that has been registered.
    ///
    /// Any user ID returned by this API must conform to the grammar given in
    /// the [Matrix specification](/appendices/#user-identifiers).
    QString userId() const { return loadFromJson<QString>("user_id"_ls); }

    /// An access token for the account.
    /// This access token can then be used to authorize other requests.
    /// Required if the `inhibit_login` option is false.
    QString accessToken() const
    {
        return loadFromJson<QString>("access_token"_ls);
    }

    /// A refresh token for the account. This token can be used to
    /// obtain a new access token when it expires by calling the
    /// `/refresh` endpoint.
    ///
    /// Omitted if the `inhibit_login` option is true.
    QString refreshToken() const
    {
        return loadFromJson<QString>("refresh_token"_ls);
    }

    /// The lifetime of the access token, in milliseconds. Once
    /// the access token has expired a new access token can be
    /// obtained by using the provided refresh token. If no
    /// refresh token is provided, the client will need to re-log in
    /// to obtain a new access token. If not given, the client can
    /// assume that the access token will not expire.
    ///
    /// Omitted if the `inhibit_login` option is true.
    Omittable<int> expiresInMs() const
    {
        return loadFromJson<Omittable<int>>("expires_in_ms"_ls);
    }

    /// ID of the registered device. Will be the same as the
    /// corresponding parameter in the request, if one was specified.
    /// Required if the `inhibit_login` option is false.
    QString deviceId() const { return loadFromJson<QString>("device_id"_ls); }
};

/*! \brief Begins the validation process for an email to be used during
 * registration.
 *
 * The homeserver must check that the given email address is **not**
 * already associated with an account on this homeserver. The homeserver
 * should validate the email itself, either by sending a validation email
 * itself or by using a service it has control over.
 */
class QUOTIENT_API RequestTokenToRegisterEmailJob : public BaseJob {
public:
    /*! \brief Begins the validation process for an email to be used during
     * registration.
     *
     * \param body
     *   The homeserver must check that the given email address is **not**
     *   already associated with an account on this homeserver. The homeserver
     *   should validate the email itself, either by sending a validation email
     *   itself or by using a service it has control over.
     */
    explicit RequestTokenToRegisterEmailJob(const EmailValidationData& body);

    // Result properties

    /// An email has been sent to the specified address. Note that this
    /// may be an email containing the validation token or it may be
    /// informing the user of an error.
    RequestTokenResponse response() const
    {
        return fromJson<RequestTokenResponse>(jsonData());
    }
};

/*! \brief Requests a validation token be sent to the given phone number for the
 * purpose of registering an account
 *
 * The homeserver must check that the given phone number is **not**
 * already associated with an account on this homeserver. The homeserver
 * should validate the phone number itself, either by sending a validation
 * message itself or by using a service it has control over.
 */
class QUOTIENT_API RequestTokenToRegisterMSISDNJob : public BaseJob {
public:
    /*! \brief Requests a validation token be sent to the given phone number for
     * the purpose of registering an account
     *
     * \param body
     *   The homeserver must check that the given phone number is **not**
     *   already associated with an account on this homeserver. The homeserver
     *   should validate the phone number itself, either by sending a validation
     *   message itself or by using a service it has control over.
     */
    explicit RequestTokenToRegisterMSISDNJob(const MsisdnValidationData& body);

    // Result properties

    /// An SMS message has been sent to the specified phone number. Note
    /// that this may be an SMS message containing the validation token or
    /// it may be informing the user of an error.
    RequestTokenResponse response() const
    {
        return fromJson<RequestTokenResponse>(jsonData());
    }
};

/*! \brief Changes a user's password.
 *
 * Changes the password for an account on this homeserver.
 *
 * This API endpoint uses the [User-Interactive Authentication
 * API](/client-server-api/#user-interactive-authentication-api) to ensure the
 * user changing the password is actually the owner of the account.
 *
 * An access token should be submitted to this endpoint if the client has
 * an active session.
 *
 * The homeserver may change the flows available depending on whether a
 * valid access token is provided. The homeserver SHOULD NOT revoke the
 * access token provided in the request. Whether other access tokens for
 * the user are revoked depends on the request parameters.
 */
class QUOTIENT_API ChangePasswordJob : public BaseJob {
public:
    /*! \brief Changes a user's password.
     *
     * \param newPassword
     *   The new password for the account.
     *
     * \param logoutDevices
     *   Whether the user's other access tokens, and their associated devices,
     * should be revoked if the request succeeds.
     *
     *   When `false`, the server can still take advantage of the [soft logout
     * method](/client-server-api/#soft-logout) for the user's remaining
     * devices.
     *
     * \param auth
     *   Additional authentication information for the user-interactive
     * authentication API.
     */
    explicit ChangePasswordJob(const QString& newPassword,
                               bool logoutDevices = true,
                               const Omittable<AuthenticationData>& auth = none);
};

/*! \brief Requests a validation token be sent to the given email address for
 * the purpose of resetting a user's password
 *
 * The homeserver must check that the given email address **is
 * associated** with an account on this homeserver. This API should be
 * used to request validation tokens when authenticating for the
 * `/account/password` endpoint.
 *
 * This API's parameters and response are identical to that of the
 * [`/register/email/requestToken`](/client-server-api/#post_matrixclientv3registeremailrequesttoken)
 * endpoint, except that
 * `M_THREEPID_NOT_FOUND` may be returned if no account matching the
 * given email address could be found. The server may instead send an
 * email to the given address prompting the user to create an account.
 * `M_THREEPID_IN_USE` may not be returned.
 *
 * The homeserver should validate the email itself, either by sending a
 * validation email itself or by using a service it has control over.
 */
class QUOTIENT_API RequestTokenToResetPasswordEmailJob : public BaseJob {
public:
    /*! \brief Requests a validation token be sent to the given email address
     * for the purpose of resetting a user's password
     *
     * \param body
     *   The homeserver must check that the given email address **is
     *   associated** with an account on this homeserver. This API should be
     *   used to request validation tokens when authenticating for the
     *   `/account/password` endpoint.
     *
     *   This API's parameters and response are identical to that of the
     *   [`/register/email/requestToken`](/client-server-api/#post_matrixclientv3registeremailrequesttoken)
     *   endpoint, except that
     *   `M_THREEPID_NOT_FOUND` may be returned if no account matching the
     *   given email address could be found. The server may instead send an
     *   email to the given address prompting the user to create an account.
     *   `M_THREEPID_IN_USE` may not be returned.
     *
     *   The homeserver should validate the email itself, either by sending a
     *   validation email itself or by using a service it has control over.
     */
    explicit RequestTokenToResetPasswordEmailJob(const EmailValidationData& body);

    // Result properties

    /// An email was sent to the given address.
    RequestTokenResponse response() const
    {
        return fromJson<RequestTokenResponse>(jsonData());
    }
};

/*! \brief Requests a validation token be sent to the given phone number for the
 * purpose of resetting a user's password.
 *
 * The homeserver must check that the given phone number **is
 * associated** with an account on this homeserver. This API should be
 * used to request validation tokens when authenticating for the
 * `/account/password` endpoint.
 *
 * This API's parameters and response are identical to that of the
 * [`/register/msisdn/requestToken`](/client-server-api/#post_matrixclientv3registermsisdnrequesttoken)
 * endpoint, except that
 * `M_THREEPID_NOT_FOUND` may be returned if no account matching the
 * given phone number could be found. The server may instead send the SMS
 * to the given phone number prompting the user to create an account.
 * `M_THREEPID_IN_USE` may not be returned.
 *
 * The homeserver should validate the phone number itself, either by sending a
 * validation message itself or by using a service it has control over.
 */
class QUOTIENT_API RequestTokenToResetPasswordMSISDNJob : public BaseJob {
public:
    /*! \brief Requests a validation token be sent to the given phone number for
     * the purpose of resetting a user's password.
     *
     * \param body
     *   The homeserver must check that the given phone number **is
     *   associated** with an account on this homeserver. This API should be
     *   used to request validation tokens when authenticating for the
     *   `/account/password` endpoint.
     *
     *   This API's parameters and response are identical to that of the
     *   [`/register/msisdn/requestToken`](/client-server-api/#post_matrixclientv3registermsisdnrequesttoken)
     *   endpoint, except that
     *   `M_THREEPID_NOT_FOUND` may be returned if no account matching the
     *   given phone number could be found. The server may instead send the SMS
     *   to the given phone number prompting the user to create an account.
     *   `M_THREEPID_IN_USE` may not be returned.
     *
     *   The homeserver should validate the phone number itself, either by
     * sending a validation message itself or by using a service it has control
     * over.
     */
    explicit RequestTokenToResetPasswordMSISDNJob(
        const MsisdnValidationData& body);

    // Result properties

    /// An SMS message was sent to the given phone number.
    RequestTokenResponse response() const
    {
        return fromJson<RequestTokenResponse>(jsonData());
    }
};

/*! \brief Deactivate a user's account.
 *
 * Deactivate the user's account, removing all ability for the user to
 * login again.
 *
 * This API endpoint uses the [User-Interactive Authentication
 * API](/client-server-api/#user-interactive-authentication-api).
 *
 * An access token should be submitted to this endpoint if the client has
 * an active session.
 *
 * The homeserver may change the flows available depending on whether a
 * valid access token is provided.
 *
 * Unlike other endpoints, this endpoint does not take an `id_access_token`
 * parameter because the homeserver is expected to sign the request to the
 * identity server instead.
 */
class QUOTIENT_API DeactivateAccountJob : public BaseJob {
public:
    /*! \brief Deactivate a user's account.
     *
     * \param auth
     *   Additional authentication information for the user-interactive
     * authentication API.
     *
     * \param idServer
     *   The identity server to unbind all of the user's 3PIDs from.
     *   If not provided, the homeserver MUST use the `id_server`
     *   that was originally use to bind each identifier. If the
     *   homeserver does not know which `id_server` that was,
     *   it must return an `id_server_unbind_result` of
     *   `no-support`.
     */
    explicit DeactivateAccountJob(
        const Omittable<AuthenticationData>& auth = none,
        const QString& idServer = {});

    // Result properties

    /// An indicator as to whether or not the homeserver was able to unbind
    /// the user's 3PIDs from the identity server(s). `success` indicates
    /// that all identifiers have been unbound from the identity server while
    /// `no-support` indicates that one or more identifiers failed to unbind
    /// due to the identity server refusing the request or the homeserver
    /// being unable to determine an identity server to unbind from. This
    /// must be `success` if the homeserver has no identifiers to unbind
    /// for the user.
    QString idServerUnbindResult() const
    {
        return loadFromJson<QString>("id_server_unbind_result"_ls);
    }
};

/*! \brief Checks to see if a username is available on the server.
 *
 * Checks to see if a username is available, and valid, for the server.
 *
 * The server should check to ensure that, at the time of the request, the
 * username requested is available for use. This includes verifying that an
 * application service has not claimed the username and that the username
 * fits the server's desired requirements (for example, a server could dictate
 * that it does not permit usernames with underscores).
 *
 * Matrix clients may wish to use this API prior to attempting registration,
 * however the clients must also be aware that using this API does not normally
 * reserve the username. This can mean that the username becomes unavailable
 * between checking its availability and attempting to register it.
 */
class QUOTIENT_API CheckUsernameAvailabilityJob : public BaseJob {
public:
    /*! \brief Checks to see if a username is available on the server.
     *
     * \param username
     *   The username to check the availability of.
     */
    explicit CheckUsernameAvailabilityJob(const QString& username);

    /*! \brief Construct a URL without creating a full-fledged job object
     *
     * This function can be used when a URL for CheckUsernameAvailabilityJob
     * is necessary but the job itself isn't.
     */
    static QUrl makeRequestUrl(QUrl baseUrl, const QString& username);

    // Result properties

    /// A flag to indicate that the username is available. This should always
    /// be `true` when the server replies with 200 OK.
    Omittable<bool> available() const
    {
        return loadFromJson<Omittable<bool>>("available"_ls);
    }
};

} // namespace Quotient