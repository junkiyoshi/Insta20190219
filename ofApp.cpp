#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int width = 35;
	int span = 240;
	int len_start = 220;
	vector<glm::vec2> outer;
	vector<glm::vec2> inner;

	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			ofPushMatrix();
			ofTranslate(x, y);
			
			for (int len = len_start; len > width; len -= width * 1.5) {

				int start = ofRandom(100) + ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.01), 0, 1, 0, 100);
				for (int param = start; param < start + 100; param++) {

					if (ofRandom(100) < 7.5) {

						if (outer.size() > 10 && param < start + 90) {

							outer.push_back(this->make_point(len, param));
							inner.push_back(this->make_point(len - width, param));

							this->draw_piece(outer, inner);
						}
					}

					outer.push_back(this->make_point(len, param));
					inner.push_back(this->make_point(len - width, param));
				}

				outer.push_back(this->make_point(len, start));
				inner.push_back(this->make_point(len - width, start));

				this->draw_piece(outer, inner);
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_piece(vector<glm::vec2>& outer, vector<glm::vec2>& inner) {

	ofColor random_color;
	random_color.setHsb(ofRandom(255), 180, 255);

	reverse(inner.begin(), inner.end());

	ofFill();
	ofSetColor(random_color);

	ofBeginShape();
	ofVertices(outer);
	ofVertices(inner);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertices(outer);
	ofVertices(inner);
	ofEndShape(true);

	outer.clear();
	inner.clear();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}