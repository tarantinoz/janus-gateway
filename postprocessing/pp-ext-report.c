#include "pp-ext-report.h"

#include <jansson.h>

#include "stdlib.h"
#include "glib.h"

#include "../debug.h"

void janus_pp_print_ext_report(janus_pp_extension_report* report) {
	json_t *obj = json_object();


	janus_pp_extension_report_rotation *rot = report->rotations;

	/* add rotations to json */
	json_t *rotations = json_array();
	while(rot) {
		json_t *elem = json_object();

		json_object_set_new(elem, "ts", json_real(rot->timestamp));
		json_object_set_new(elem, "rotation", json_integer(rot->rotation));

		json_array_append_new(rotations, elem);
		rot = rot->next;
	}
	json_object_set_new(obj, "rotations", rotations);

	char *str = json_dumps(obj, JSON_INDENT(0) | JSON_PRESERVE_ORDER);
	JANUS_PRINT("%s\n", str);
	free(str);

	json_decref(obj);
}

void janus_pp_free_ext_report(janus_pp_extension_report* report) {
	if(!report) {
		return;
	}

	janus_pp_extension_report_rotation *current = report->rotations;
	while(current) {
		janus_pp_extension_report_rotation* next = current->next;
		g_free(current);
		current = next;
	}

	g_free(report);
}

janus_pp_extension_report* janus_pp_create_ext_report(void) {
	janus_pp_extension_report* report = g_malloc(sizeof(janus_pp_extension_report));
	report->rotations = NULL;
	return report;
}

void janus_pp_add_ext_rotation(janus_pp_extension_report* report, double timestamp, int rotation) {
	janus_pp_extension_report_rotation* entry = g_malloc(sizeof(janus_pp_extension_report_rotation));
	entry->rotation = rotation;
	entry->timestamp = timestamp;
	entry->next = NULL;

	if(!report->rotations) {
		report->rotations = entry;
		return;
	}

	janus_pp_extension_report_rotation* prev = report->rotations;
	while(prev->next) {
		prev = prev->next;
	}
	prev->next = entry;
}

void janus_pp_detect_rotation_changes(janus_pp_extension_report *report, janus_pp_frame_packet *list) {
	janus_pp_frame_packet *tmp = list;
	while (tmp) {
		if(tmp->rotation != -1 && tmp->rotation != rotation) {
			int rotation = tmp->rotation;
			double ts = (double)(tmp->ts-list->ts)/(double)90000;
			janus_pp_add_ext_rotation(report, ts, rotation);
		}

		tmp = tmp->next;
	}
}