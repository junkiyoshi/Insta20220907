#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	float phi_deg_step = 6;
	float theta_deg_step = 6;
	float R = 300;
	float threshold = 0.52;

	ofColor color_1;
	for (float r = 25; r <= 75; r += 10) {

		color_1.setHsb(ofMap(r, 25, 75, 0, 255), 200, 255);
		ofColor color_2 = ofColor(239);
		color_2 = color_1;
		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg) * 0.004, ofGetFrameNum() * 0.005));
				if (noise_value < threshold) { continue; }

				auto noise_1 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg - theta_deg_step, phi_deg) * 0.004, ofGetFrameNum() * 0.005));
				auto noise_2 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg + phi_deg_step) * 0.004, ofGetFrameNum() * 0.005));
				auto noise_3 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg - phi_deg_step) * 0.004, ofGetFrameNum() * 0.005));
				auto noise_4 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg + theta_deg_step, phi_deg) * 0.004, ofGetFrameNum() * 0.005));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

				this->face.addVertices(vertices);

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(color_1);
				}

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				if (noise_1 < threshold) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[2]);

					this->frame.addColor(color_2);
					this->frame.addColor(color_2);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_2 < threshold) {

					this->frame.addVertex(vertices[2]);
					this->frame.addVertex(vertices[3]);

					this->frame.addColor(color_2);
					this->frame.addColor(color_2);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_3 < threshold) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[1]);

					this->frame.addColor(color_2);
					this->frame.addColor(color_2);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_4 < threshold) {

					this->frame.addVertex(vertices[1]);
					this->frame.addVertex(vertices[3]);

					this->frame.addColor(color_2); 
					this->frame.addColor(color_2);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	this->frame.draw();
	//this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ???w?f?b?T?????? ?`?????y???????w?????@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}