package backend

import (
	"errors"
	"os/exec"
	"regexp"
)

type AdbBackend struct{}

func (t *AdbBackend) GetName() string {
	return "Android"
}

func (t *AdbBackend) ListDevices() ([]AdbDevice, error) {
	out, err := exec.Command("adb", "devices", "-l").Output()
	if err != nil {
		return nil, err
	}

	lines := regexp.MustCompile("\r?\n").Split(string(out), -1)
	if lines[0] != "List of devices attached" {
		return nil, errors.New(string(out))
	}

	var devices []AdbDevice
	for _, line := range lines[1:] {
		if len(line) == 0 {
			continue
		}

		found := regexp.MustCompile("^([a-zA-Z0-9\\-]+)(\\s+)(device )(.*?)").FindStringSubmatch(line)
		if len(line) != 5 {
			continue
		}
		devices = append(devices, AdbDevice{
			DeviceId:    found[1],
			Description: found[4],
		})
	}

	return devices, nil
}

type AdbDevice struct {
	DeviceId    string
	Description string
}
