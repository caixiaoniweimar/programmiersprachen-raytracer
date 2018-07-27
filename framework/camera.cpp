Camera::Camera():
	name_{"default name fuer Camera"},
	fov_x_{0.0f} {}

Camera::Camera(string const& name, float fov_x):
	name_{name},
	fov_x_{fov_x} {}