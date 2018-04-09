/* Implementation file of Aquatic */

#include "aquatic/Aquatic.hpp"
#include "aquarium/Aquarium.hpp"

Aquatic::Aquatic(Aquarium *aquarium) : moveSpeed(0) {
	x = 0;
	y = 0;
	last_curr_time = this->getAquarium()->getCurrTime();
	this->aquarium = aquarium;
}

Aquatic::Aquatic(double x, double y, double move_speed, Aquarium *aquarium) : moveSpeed(move_speed) {
	this->x = x;
	this->y = y;
	this->last_curr_time = aquarium->getCurrTime();
	this->aquarium = aquarium;
}

Aquarium *Aquatic::getAquarium() {
	return this->aquarium;
}

double Aquatic::getMoveSpeed() const {
	return this->moveSpeed;
}

double Aquatic::getX() {
	return this->x;
}

double Aquatic::getY() {
	return this->y;
}

double Aquatic::getLastCurrTime() const {
	return this->last_curr_time;
}

void Aquatic::setX(double x) {
	this->x = x;
}

void Aquatic::setY(double y) {
	this->y = y;
}

void Aquatic::setLastCurrTime(double t) {
	this->last_curr_time = t;
}

bool Aquatic::isInside() {
	return x >= 0 && y >= 0 && y < this->aquarium->getYMax() && x < this->aquarium->getXMax();
}