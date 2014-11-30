#include "apierror.h"

const char *janus_get_api_error(int error) {
	switch(error) {
		case JANUS_OK:
			return "Success";
		case JANUS_ERROR_UNAUTHORIZED:
			return "Unauthorized request (wrong or missing secret)";
		case JANUS_ERROR_UNKNOWN:
			return "Unknown error";
		case JANUS_ERROR_USE_GET:
			return "Use GET";
		case JANUS_ERROR_USE_POST:
			return "Use POST";
		case JANUS_ERROR_MISSING_REQUEST:
			return "Missing request";
		case JANUS_ERROR_UNKNOWN_REQUEST:
			return "Unknown request";
		case JANUS_ERROR_INVALID_JSON:
			return "Invalid JSON";
		case JANUS_ERROR_INVALID_JSON_OBJECT:
			return "Invalid JSON Object";
		case JANUS_ERROR_MISSING_MANDATORY_ELEMENT:
			return "Missing mandatory element";
		case JANUS_ERROR_INVALID_REQUEST_PATH:
			return "Invalid path for this request";
		case JANUS_ERROR_SESSION_NOT_FOUND:
			return "Session not found";
		case JANUS_ERROR_HANDLE_NOT_FOUND:
			return "Handle not found";
		case JANUS_ERROR_PLUGIN_NOT_FOUND:
			return "Plugin not found";
		case JANUS_ERROR_PLUGIN_ATTACH:
			return "Error attaching plugin";
		case JANUS_ERROR_PLUGIN_MESSAGE:
			return "Error sending message to plugin";
		case JANUS_ERROR_PLUGIN_DETACH:
			return "Error detaching from plugin";
		case JANUS_ERROR_JSEP_UNKNOWN_TYPE:
			return "Unsupported JSEP type";
		case JANUS_ERROR_JSEP_INVALID_SDP:
			return "Invalid SDP";
		case JANUS_ERROR_TRICKE_INVALID_STREAM:
			return "Invalid stream";
		case JANUS_ERROR_INVALID_ELEMENT_TYPE:
			return "Invalid element type";
		case JANUS_ERROR_SESSION_CONFLICT:
			return "Session ID already in use";
		case JANUS_ERROR_UNEXPECTED_ANSWER:
			return "Unexpected ANSWER (no OFFER)";
		default:
			return "Unknown error";
	}
	return "Unknown error";
}
