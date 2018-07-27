LIGHT::LIGHT():
	name_{"default name fuer light"},
	position_{0.0f,0.0f,0.0f},
	color_{1.0f,1.0f,1.0f},
	brightness_{1.0f} {}

LIGHT::LIGHT(string const& name, glm::vec3 position, Color const& color, float brightness):
	name_{name},
	position_{position},
	color_{color},
	brightness_{brightness} {}