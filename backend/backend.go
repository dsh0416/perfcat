package backend

type Backend interface {
	GetName() string
	ListDevices() ([]Device, error)
}

type Device interface {
	GetName() string
	ListSurfaces() ([]Surface, error)

	GetDeviceName() (string, error)
	GetCpuUsage() (float64, error)
	GetMemoryUsage() (float64, error)
	GetGpuUsage() (float64, error)
}

type Surface interface {
	GetName() string // the human-readable resource of the system
	IsTracking() bool
	StartTracking(frame chan Frame, quit chan int64) error
	StopTracking() error
}

type Frame struct {
	FrameTime         uint64 // in nanoseconds
	IntendedFrameTime uint64 // in nanoseconds
}
