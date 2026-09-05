
const float a = glm::sqrt(2.0f) * 0.5f;
float verticies[] = {
	-a, 0., -a,
	-a, 0., a,
	a, 0., -a,
	a, 0., a,
	0., -1., 0.,
	0., 1., 0.
};

int indicies[]{
	0, 1, 4,
	0, 1, 5,
	1, 3, 4,
	1, 3, 5,
	3, 2, 4,
	3, 2, 5,
	0, 2, 4,
	0, 2, 5
};