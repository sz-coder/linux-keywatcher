#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>

char *get_apple_magic_keyboard() {
	struct dirent **namelist;
	int n = scandir("/dev/input/by-id/", &namelist, NULL, alphasort);

	if (n == -1) {
		return NULL;
	}

	char *magic_keyboard_path = NULL;

	while (n--) {
		const char *name = namelist[n]->d_name;

		if (strstr(name, "Magic_Keyboard") != NULL && magic_keyboard_path == NULL) {
			magic_keyboard_path = strdup(name);
		}

		free(namelist[n]);
	}

	free(namelist);

	if (!magic_keyboard_path) {
		return NULL;
	}

	char *buffer = malloc(300);

	if (!buffer) {
		fprintf(stderr, "malloc() failed.\n");
		exit(1);
	}

	if (0 > snprintf(buffer, 300, "/dev/input/by-id/%s", magic_keyboard_path)) {
		fprintf(stderr, "snprintf() failed.\n");
		exit(1);
	}

	free(magic_keyboard_path);

	printf("Found apple magic keyboard at: %s\n", buffer);

	return buffer;
}

#define DELAY() do { usleep(100 * 1E3); } while (0)

int main(void) {
	while (true) {
		char *device_path = get_apple_magic_keyboard();

		if (!device_path) {
			DELAY();
			continue;
		}

		printf("Found apple magic keyboard at %s\n", device_path);

		int keyboard_fd = open(device_path, O_RDONLY);

		if (0 > keyboard_fd) {
			free(device_path);
			fprintf(stderr, "Failed to open device_path.\n");
			DELAY();
			continue;
		}

		printf("Successfully opened device path.\n");

		while (true) {
			struct input_event event;
			int bytesRead = read(keyboard_fd, &event, sizeof(event));

			if (0 > bytesRead) {
				fprintf(stderr, "Failed to read bytes from device path.\n");
				break;
			}

			if (event.type == EV_KEY && event.value == 1) {
				if (event.code == 0x36) {
					system("/usr/bin/curl http://10.10.10.10:4444/toggle-usb-switch --max-time 3 -o /dev/null 1> /dev/null 2>/dev/null &");
				}
			}
		}

		free(device_path);
		DELAY();
	}

	return EXIT_SUCCESS;
}
