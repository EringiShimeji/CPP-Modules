#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) {
	this->value = value << fractional_bits;
}

Fixed::Fixed(const float value) {
	this->value = roundf(value * (1 << fractional_bits));
}

Fixed::Fixed(const Fixed &fixed) : value(fixed.value) {
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	value = fixed.value;
	return *this;
}

int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return value;
}

void Fixed::setRawBits(const int raw) {
	value = raw;
}

float Fixed::toFloat() const {
	return (float) this->value / (1 << fractional_bits);
}

float Fixed::toInt() const {
	return this->value >> fractional_bits;
}

bool Fixed::operator>(const Fixed &rhs) const {
	return this->getRawBits() > rhs.getRawBits();
}

bool Fixed::operator<(const Fixed &rhs) const {
	return rhs > *this;
}

bool Fixed::operator>=(const Fixed &rhs) const {
	return *this > rhs || *this == rhs;
}

bool Fixed::operator<=(const Fixed &rhs) const {
	return rhs >= *this;
}

bool Fixed::operator==(const Fixed &rhs) const {
	return this->getRawBits() == rhs.getRawBits();
}

bool Fixed::operator!=(const Fixed &rhs) const {
	return !(*this == rhs);
}

Fixed Fixed::operator+(const Fixed &rhs) const {
	return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed &rhs) const {
	return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed &rhs) const {
	return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed &rhs) const {
	return Fixed(this->toFloat() / rhs.toFloat());
}

const Fixed Fixed::operator++(int _v) {
	(void) _v;
	Fixed tmp = *this;

	setRawBits(this->getRawBits() + 1);
	return tmp;
}

const Fixed Fixed::operator--(int _v) {
	(void) _v;
	Fixed tmp = *this;

	setRawBits(this->getRawBits() - 1);
	return tmp;
}

Fixed &Fixed::operator++() {
	setRawBits(this->getRawBits() + 1);
	return *this;
}

Fixed &Fixed::operator--() {
	setRawBits(this->getRawBits() - 1);
	return *this;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a < b)
		return a;
	return b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	if (a < b)
		return a;
	return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a > b)
		return a;
	return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	if (a > b)
		return a;
	return b;
}

std::ostream &operator<<(std::ostream &stream, const Fixed &value) {
	return stream << value.toFloat();
}
