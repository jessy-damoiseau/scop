#include <parser/parser.hpp>

Parser::Parser(const std::string& filePath) {
	std::ifstream file(filePath);
	std::string line;
	std::vector<std::vector<u_int>> indices_tmp;
	_minx = 0;
	_miny = 0;
	_maxx = 0;
	_maxy = 0;
	_maxz = 0;
	_minz = 0;

	if (!file.is_open()) {
		std::cout << "ERROR::.obj::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return;
	}

	while (std::getline(file, line)) {
		if (!line.empty() && (line[0] == 'v' || line[0] == 'f')) {
			std::istringstream iss(line);
			char type;
			iss >> type;

			if (type == 'v') {
				float x, y, z;
				iss >> x >> y >> z;
				_vertex.push_back(x);
				_vertex.push_back(y);
				_vertex.push_back(z);
				if (_maxx < x)
					_maxx = x;
				if (_maxy < y)
					_maxy = y;
				if (_minx > x)
					_minx = x;
				if (_miny > y)
					_miny = y;
				if (_maxz < z)
					_maxz = z;
				if (_minz > z)
					_minz = z;
			} else if (type == 'f') {
				std::string vertexIndices;
				std::vector<u_int> tmp;
				std::vector<u_int> face_indices;
				while (iss >> vertexIndices) {
					size_t pos;
					unsigned int index = std::stoul(vertexIndices, &pos);
					if (pos == vertexIndices.size()) {
						tmp.push_back(index);
					} else {
						std::cout << "Invalid face index format: " << vertexIndices << std::endl;
					}
				}
				for (size_t i = 0; i < tmp.size() - 2; ++i) {
					face_indices.push_back(tmp[0] - 1);
					face_indices.push_back(tmp[i + 1] - 1);
					face_indices.push_back(tmp[i + 2] - 1);
				}
				indices_tmp.push_back(face_indices);
			}

		}
	}
	file.close();
	centerVertex();
	faceIndices(indices_tmp);
}

void Parser::centerVertex() {
	float x = 0;
	float y = 0;
	float z = 0;
	for (size_t i = 0; i < _vertex.size(); i += 3) {
		x += _vertex[i];
		y += _vertex[i + 1];
		z += _vertex[i + 2];
	}
	x /= _vertex.size() / 3;
	y /= _vertex.size() / 3;
	z /= _vertex.size() / 3;
	for (size_t i = 0; i < _vertex.size(); i += 3) {
		_vertex[i] -= x;
		_vertex[i + 1] -= y;
		_vertex[i + 2] -= z;
	}
}


void Parser::faceIndices(std::vector<std::vector<u_int>> indices_tmp) {
	std::vector<float> new_vertex;
	std::vector<u_int> new_indices;
	u_int index = 0;
	u_int face = 0;

	for (size_t i = 0; i < indices_tmp.size(); ++i) {
		std::vector<u_int> tmp_indices;
		for (size_t j = 0; j < indices_tmp[i].size(); ++j) {
			if (!tmp_indices.size() || std::find(tmp_indices.begin(), tmp_indices.end(), indices_tmp[i][j]) == tmp_indices.end()){
				tmp_indices.push_back(indices_tmp[i][j]);
				new_vertex.push_back(_vertex[indices_tmp[i][j] * 3]);
				new_vertex.push_back(_vertex[indices_tmp[i][j] * 3 + 1]);
				new_vertex.push_back(_vertex[indices_tmp[i][j] * 3 + 2]);
				setFaceColor(face, new_vertex);
				setTextureCords(new_vertex);
				new_indices.push_back(index++);
			}
			else {
				int indice_index = std::find(tmp_indices.begin(), tmp_indices.end(), indices_tmp[i][j]) - tmp_indices.begin();
				new_indices.push_back(std::fabs((indice_index - tmp_indices.size()) + index));
			}
		}
		face++;
	}
	_vertex = new_vertex;
	_indices = new_indices;
}

void Parser::setFaceColor(u_int face, std::vector<float> &Vertex){
	if (face % 5 == 0){
		Vertex.push_back(0.0f);
		Vertex.push_back(0.0f);
		Vertex.push_back(0.0f);
	}else if (face % 5 == 1){
		Vertex.push_back(0.25f);
		Vertex.push_back(0.25f);
		Vertex.push_back(0.25f);
	}else if (face % 5 == 2){
		Vertex.push_back(0.5f);
		Vertex.push_back(0.5f);
		Vertex.push_back(0.5f);
	}else if (face % 5 == 3){
		Vertex.push_back(0.75f);
		Vertex.push_back(0.75f);
		Vertex.push_back(0.75f);
	}else if (face % 5 == 4){
		Vertex.push_back(1.0f);
		Vertex.push_back(1.0f);
		Vertex.push_back(1.0f);
	}
}

void Parser::setTextureCords(std::vector<float> &Vertex){
	float x = 0;
	float y = 0;
	x = (Vertex[Vertex.size() - 5] - _miny) / _maxy;
	y = ((Vertex[Vertex.size() - 4] - _minz) / _maxz) * -1;
	Vertex.push_back(y);
	Vertex.push_back(x);
}

void Parser::printVertex() const {
	int tmp = 0;
	for (size_t i = 0; i < _vertex.size(); i += 3) {
		std::cout << "x"<< tmp << ": " << _vertex[i] << " y"<< tmp + 1 << ": " << _vertex[i + 1] << " z"<< tmp + 2 << ": " << _vertex[i + 2] << std::endl;
		tmp += 3;
	}
}

void Parser::printIndices() const {
	for (size_t i = 0; i < _indices.size(); i += 3) {
		std::cout << "x: " << _indices[i] << " y: " << _indices[i + 1] << " z: " << _indices[i + 2] << std::endl;
	}
}


const std::vector<float> &Parser::getVertex() const {
    return _vertex;
}

const std::vector<u_int> &Parser::getIndices() const {
    return _indices;
}



Parser::~Parser() = default;
