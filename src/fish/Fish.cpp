/* Implementation file of Fish */
#include "../fish/Fish.hpp"

Fish::Fish(int food_thres, double eat_radius, double full_interval, double hunger_timeout, double created_time) : foodThres(food_thres), eatRadius(eat_radius), fullInterval(full_interval), hungerTimeout(hunger_timeout) {
	last_eat_time = created_time;
	last_random_time = created_time;
	last_hunger_time = created_time;
	food_eaten = 0;
	hungry = false;
	level = 1;
}

/* Getter and Setter */
double Fish::getLastEatTime() {
	return last_eat_time;
}

double Fish::getLastRandomTime() {
	return last_random_time;
}

int Fish::getFoodEaten() {
	return food_eaten;
}

bool Fish::getHungry() {
	return hungry;
}

int Fish::getLevel() {
 	return level;
}

Direction Fish::getDirection() {
	return x_dir >= 0 ? Direction::right : Direction::left;
}

void Fish::setLastEatTime(double last_eat_time) {
	this->last_eat_time = last_eat_time;
}

void Fish::setLastRandomTime(double last_random_time) {
	this->last_random_time = last_random_time;
}

void Fish::setFoodEaten(int food_eaten) {
	this->food_eaten = food_eaten;
}

void Fish::setHungry(bool hungry) {
	this->hungry = hungry;
}

void Fish::setLevel(int level) {
	this->level = level;
}
