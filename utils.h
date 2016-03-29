/*! \file    utils.h
 * \author   Lorenzo Miniero <lorenzo@meetecho.com>
 * \copyright GNU General Public License v3
 * \brief    Utilities and helpers (headers)
 * \details  Implementations of a few methods that may be of use here
 * and there in the code.
 * 
 * \ingroup core
 * \ref core
 */
 
#ifndef _JANUS_UTILS_H
#define _JANUS_UTILS_H

#include <stdint.h>
#include <glib.h>
#include <netinet/in.h>
#include <jansson.h>

struct janus_json_parameter {
	const gchar *name;
	json_type jtype;
	gboolean positive_non_empty;
	gboolean required;
};

/*! \brief Helper to retrieve the system monotonic time, as Glib's
 * g_get_monotonic_time may not be available (only since 2.28)
 * @returns The system monotonic time */
gint64 janus_get_monotonic_time(void);

/*! \brief Helper to retrieve the system real time, as Glib's
 * g_get_real_time may not be available (only since 2.28)
 * @returns The system real time */
gint64 janus_get_real_time(void);

/*! \brief Helper to replace strings
 * @param message The string that contains the text to replace, which may be
 * freed if it is too short
 * @param old_string The old text to replace
 * @param new_string The new text
 * @returns A pointer to the updated text string (re-allocated or just updated) */
char *janus_string_replace(char *message, const char *old_string, const char *new_string) G_GNUC_WARN_UNUSED_RESULT;

/*! \brief Helper to parse yes/no|true/false configuration values
 * @param value The configuration value to parse
 * @returns true if the value contains a "yes", "YES", "true", TRUE", "1", false otherwise */
gboolean janus_is_true(const char *value);

/*! \brief Helper to compare strings in constant time
 * @param str1 The first string to compare
 * @param str2 The second string to compare
 * @returns true if the strings are the same, false otherwise */
gboolean janus_strcmp_const_time(const void *str1, const void *str2);

/** @name Flags helper methods
 */
///@{
/*! \brief Janus flags container */
typedef uint32_t janus_flags;

/*! \brief Janus flags reset method
 * \param[in] flags The janus_flags instance to reset */
void janus_flags_reset(janus_flags *flags);

/*! \brief Janus flags set method
 * \param[in] flags The janus_flags instance to update
 * \param[in] flag The flag to set */
void janus_flags_set(janus_flags *flags, uint32_t flag);

/*! \brief Janus flags clear method
 * \param[in] flags The janus_flags instance to update
 * \param[in] flag The flag to clear */
void janus_flags_clear(janus_flags *flags, uint32_t flag);

/*! \brief Janus flags check method
 * \param[in] flags The janus_flags instance to check
 * \param[in] flag The flag to check
 * \returns true if the flag is set, false otherwise */
gboolean janus_flags_is_set(janus_flags *flags, uint32_t flag);
///@}

/*! \brief Helper to create a new directory, and recursively create parent directories if needed
 * @param dir Path to the new folder to create
 * @param mode File permissions for the new directory file
 * @returns An integer like the regular mkdir does
 * @note A failure may indicate that creating any of the subdirectories failed: some may still have been created */
int janus_mkdir(const char *dir, mode_t mode);

/*! \brief Ugly and dirty helper to quickly get the Opus payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The Opus payload type, if found, -1 otherwise */
int janus_get_opus_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the ISAC 32K payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The ISAC 32K payload type, if found, -1 otherwise */
int janus_get_isac32_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the ISAC 16K payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The ISAC 16K payload type, if found, -1 otherwise */
int janus_get_isac16_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the PCMU payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The PCMU payload type, if found, -1 otherwise */
int janus_get_pcmu_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the PCMU payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The PCMA payload type, if found, -1 otherwise */
int janus_get_pcma_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the VP8 payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The VP8 payload type, if found, -1 otherwise */
int janus_get_vp8_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the VP9 payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The VP9 payload type, if found, -1 otherwise */
int janus_get_vp9_pt(const char *sdp);

/*! \brief Ugly and dirty helper to quickly get the H.264 payload type in an SDP
 * @param sdp The SDP to parse
 * @returns The H.264 payload type, if found, -1 otherwise */
int janus_get_h264_pt(const char *sdp);

/*! \brief Check if the given IP address is valid: family is set to the address family if the IP is valid
 * @param ip The IP address to check
 * @param[in,out] family The address family of the address, set by the method if valid
 * @returns true if the address is valid, false otherwise */
gboolean janus_is_ip_valid(const char *ip, int *family);

/*! \brief Convert a sockaddr address to an IP string
 * \note The resulting string is allocated, which means the caller must free it itself when done
 * @param address The sockaddr address to convert
 * @returns A string containing the IP address, if successful, NULL otherwise */
char *janus_address_to_ip(struct sockaddr *address);

/*! \brief Create and lock a PID file
 * @param file Path to the PID file to use
 * @returns 0 if successful, a negative integer otherwise */
int janus_pidfile_create(const char *file);

/*! \brief Unlock and remove a previously created PID file
 * @returns 0 if successful, a negative integer otherwise */
int janus_pidfile_remove(void);

void janus_get_json_type_name(int jtype, gboolean positive_non_empty, char *type_name);
gboolean janus_json_is_valid(json_t *val, json_type jtype, gboolean positive_non_empty);

#define JANUS_VALIDATE_JSON_OBJECT_FORMAT(missing_format, invalid_format, root, params, error_code, error_cause, log_error, missing_code, invalid_code) \
	do { \
		unsigned int i; \
		for(i = 0; i < sizeof(params) / sizeof(struct janus_json_parameter); i++) { \
			json_t *val = json_object_get(root, params[i].name); \
			if(!val) { \
				if(params[i].required) { \
					error_code = (missing_code); \
					if(log_error) \
						JANUS_LOG(LOG_ERR, missing_format "\n", params[i].name); \
					if(error_cause != NULL) \
						g_snprintf(error_cause, sizeof(error_cause), missing_format, params[i].name); \
					break; \
				} \
				continue; \
			} \
			if(!janus_json_is_valid(val, params[i].jtype, params[i].positive_non_empty)) { \
				error_code = (invalid_code); \
				char type_name[20]; \
				janus_get_json_type_name(params[i].jtype, params[i].positive_non_empty, type_name); \
				if(log_error) \
					JANUS_LOG(LOG_ERR, invalid_format "\n", params[i].name, type_name); \
				if(error_cause != NULL) \
					g_snprintf(error_cause, sizeof(error_cause), invalid_format, params[i].name, type_name); \
				break; \
			} \
		} \
	} while(0)

#define JANUS_VALIDATE_JSON_OBJECT(root, params, error_code, error_size, log_error, missing_code, invalid_code) \
	JANUS_VALIDATE_JSON_OBJECT_FORMAT("Missing mandatory element (%s)", "Invalid element type (%s should be %s)", root, params, error_code, error_cause, log_error, missing_code, invalid_code)

#endif
