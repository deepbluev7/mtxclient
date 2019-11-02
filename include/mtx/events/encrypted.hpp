#pragma once

#include <nlohmann/json_fwd.hpp>

#include "mtx/events.hpp"

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace msg {

struct OlmCipherContent
{
        std::string body;
        uint8_t type;
};

void
from_json(const json &obj, OlmCipherContent &event);

void
to_json(json &obj, const OlmCipherContent &event);

//! Content of the `m.room.encrypted` Olm event.
struct OlmEncrypted
{
        std::string algorithm;
        std::string sender_key;

        using RecipientKey = std::string;
        std::map<RecipientKey, OlmCipherContent> ciphertext;
};

void
from_json(const json &obj, OlmEncrypted &event);

void
to_json(json &obj, const OlmEncrypted &event);

//! Content of the `m.room.encrypted` event.
struct Encrypted
{
        //! Used for one-on-one exchanges.
        std::string algorithm;
        //! The actual encrypted payload.
        std::string ciphertext;
        //! Sender's device id.
        std::string device_id;
        //! The curve25519 device key.
        std::string sender_key;
        //! Outbound group session id.
        std::string session_id;
};

void
from_json(const json &obj, Encrypted &event);

void
to_json(json &obj, const Encrypted &event);

//! Content of the `m.room_key` event.
struct RoomKey
{
        std::string algorithm;
        std::string room_id;
        std::string session_id;
        std::string session_key;
};

void
from_json(const json &obj, RoomKey &event);

void
to_json(json &obj, const RoomKey &event);

enum class RequestAction
{
        // request
        Request,
        // request_cancellation
        Cancellation,
        // not handled
        Unknown,
};

struct KeyRequest
{
        //! The type of request.
        RequestAction action;

        //! The encryption algorithm of the session we want keys for.
        //! Always m.megolm.v1.aes-sha2.
        std::string algorithm;
        //! The room in which the session was created.
        std::string room_id;
        //! The curve25519 key of the session creator.
        std::string sender_key;
        //! The session_id of the outbound megolm session.
        std::string session_id;

        //! A unique identifier for this request.
        std::string request_id;
        //! The device requesting the keys.
        std::string requesting_device_id;

        //! The user that send this event.
        std::string sender;
        //! The type of the event.
        mtx::events::EventType type;
};

void
from_json(const json &obj, KeyRequest &event);

void
to_json(json &obj, const KeyRequest &event);

//! Content of the `m.key.verification.request` event
struct KeyVerificationRequest
{
        //! The device ID which is initiating the request.
        std::string from_device;
        //! An opaque identifier for the verification request. Must be unique with respect to the
        //! devices involved.
        std::string transaction_id;
        //! The verification methods supported by the sender.
        std::vector<std::string> methods;
        //! The POSIX timestamp in milliseconds for when the request was made. If the request is in
        //! the future by more than 5 minutes or more than 10 minutes in the past, the message
        //! should be ignored by the receiver.
        uint64_t timestamp;
        //! The type of the event.
        mtx::events::EventType type;
};

// TODO: KeyVerificationStart, KeyVerificationAccept, and KeyVerificationCancel

void
from_json(const json &obj, KeyVerificationRequest &event);

void
to_json(json &obj, const KeyVerificationRequest &event);

} // namespace msg
} // namespace events
} // namespace mtx
