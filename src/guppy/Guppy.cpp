/* Implementation file of Guppy */
#include "../guppy/Guppy.hpp"
#include "../aquarium/Aquarium.hpp"

const int guppyFoodThres = 20;
const double guppyEatRadius = 1.25;
const double guppyFullInterval = 5; /* Ini detik ye bos */
const double guppyHungerInterval = 10;
const double guppyMoveSpeed = 10;
const double randomMoveInterval = 4; /* Ini juga detik ya brok */
const double pi = 3.14159265;
const double guppyCoinInterval = 8;
const double guppyCoinMultiplier = 10;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Guppy::Guppy(Aquarium *aquarium) : Fish(guppyFoodThres, guppyEatRadius, guppyFullInterval, guppyHungerInterval, this->getAquarium()->getCurrTime()), Aquatic(floor(fRand(0, this->getAquarium()->getXMax())), floor(fRand(0, this->getAquarium()->getYMax())), guppyMoveSpeed, aquarium) {
	nearest_pellet = NULL;
	last_drop_coin = this->getAquarium()->getCurrTime();
	x_dir = 0;
	y_dir = 0;
}

double Guppy::distanceToPellet(Pellet *p) {
	double guppy_x_position = this->getX();
	double guppy_y_position = this->getY();
	double pellet_x_position = p->getX();
	double pellet_y_position = p->getX();

	return sqrt((guppy_x_position - pellet_x_position) * (guppy_x_position - pellet_x_position) + (guppy_y_position - pellet_y_position) * (guppy_y_position - pellet_y_position));
}

void Guppy::findNearestPellet() {
	LinkedList<Pellet*> ll = this->getAquarium()->getPelletList();
	Pellet* current_nearest_pellet = NULL;
	Node<Pellet*>* curr_node = ll.getHead();
	while(curr_node != NULL) {
	    curr_node = curr_node->getNext();
	    Pellet* current_pellet = curr_node->getValue();
	    if(current_nearest_pellet == NULL) {
	    	current_nearest_pellet = current_pellet;
	    } else if(distanceToPellet(current_pellet) > distanceToPellet(current_nearest_pellet)) {
	    	current_nearest_pellet = current_pellet;
	    }
	}
	this->nearest_pellet =  current_nearest_pellet;
}

bool Guppy::nearestPelletInRange() {
	if(nearest_pellet == NULL) {
		return false;
	} else if(distanceToPellet(nearest_pellet) < this->eatRadius) {
		return true;
	} else {
		return false;
	}
}

/* Change hunger status */
void Guppy::updateState() {
	double current_time = this->getAquarium()->getCurrTime();
	if(current_time - this->getLastCurrTime() > this->hungerTimeout) {
		/* Dead guppy */
		this->getAquarium()->getGuppyList().remove(this);
	} else {
		dropCoin();
		this->findNearestPellet();
		eat();
		this->findNearestPellet();
		move();
		this->setLastCurrTime(current_time);
	}
}

void Guppy::move() {
	double current_time = this->getAquarium()->getCurrTime();
	if(nearest_pellet != NULL && this->getHungry()) {
		double x_direction = nearest_pellet->getX() - this->getX();
		double y_direction = nearest_pellet->getY() - this->getY();
		double distance = distanceToPellet(nearest_pellet);

		double dx = (x_direction / distance) * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000); /* Gue masih asumsikan kalo current time dalem ms */
		double dy = (y_direction / distance) * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000); /* Kabari kalo misalkan dalam fps atau satuan lain */

		this->setX(this->getX() + dx);
		this->setY(this->getY() + dy);
		this->x_dir = x_direction;
	} else {
		/* Random movement guppy */
		if(current_time - this->getLastRandomTime() > randomMoveInterval) {
			this->setLastRandomTime(current_time);
			double rad = fRand(0, 360) * pi / 180;

			this->x_dir = cos(rad);
			this->y_dir = sin(rad);
		}
		double dx = this->x_dir * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000);
		double dy = this->y_dir * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000);

		if(this->getX() + dx > this->getAquarium()->getXMax()) {
			this->x_dir *= -1;
			dx = this->x_dir * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000);
		} 

		if(this->getY() + dy > this->getAquarium()->getYMax()) {
			this->y_dir *= -1;
			dy = this->y_dir * this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000);
		}

		this->setX(this->getX() + dx);
		this->setY(this->getY() + dy);
	}
}

/* TODO: Implement naik level */
void Guppy::eat() {
	double current_time = this->getAquarium()->getCurrTime();
	if(!this->getHungry() && (current_time - this->getLastEatTime() > this->fullInterval)) {
		/* Change guppy hunger state */
		this->setHungry(true);
	}

	if(this->getHungry() && nearestPelletInRange()) {
		this->getAquarium()->deletePellet(nearest_pellet);
		nearest_pellet = NULL;
		this->setHungry(false);
		this->setLastEatTime(current_time);
	} 
}

void Guppy::dropCoin() {
	double current_time = this->getAquarium()->getCurrTime();
	if(current_time - this->last_drop_coin > guppyCoinInterval) {
		this->getAquarium()->createCoin(this->getX(), this->getY(), this->getLevel() * guppyCoinMultiplier);
	}
}
