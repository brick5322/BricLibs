#pragma once

#include "pubdefs.h"
class _Spliter_Iterator;
class Spliter_group;

class Spliter
{
	friend class Spliter_group;
	friend class _Spliter_Iterator;
public:
	using iterator = _Spliter_Iterator;

	Spliter(char separator,Flag flag = copy);
	~Spliter();
	size_t maxSize();
	void setSpliterByte(char separator);
	int operator<<(const char*);
	Spliter_group operator[](int pos) const;



private:
	char separator;
	size_t max_len;
	Flag flag;
	const char* str;
	char* itorbuffer;
	BasicList* spliter;
};

class Spliter_group
{
	friend class Spliter;
	friend class _Spliter_Iterator;
public:
	char* operator>>(char*);
private:
	const Spliter& parent;
	void operator=(const Spliter_group&);
	Spliter_group(const Spliter* parent, int pos);
	int pos;
	const char* str;
	int sz;
};

class _Spliter_Iterator
{
public:
	_Spliter_Iterator(const Spliter&, int pos = 0);
	_Spliter_Iterator(const Spliter& parent, int pos, char* buffer);
	_Spliter_Iterator(const _Spliter_Iterator&);
	_Spliter_Iterator(_Spliter_Iterator&&);
	~_Spliter_Iterator();
	_Spliter_Iterator begin();
	_Spliter_Iterator end();
	_Spliter_Iterator& operator++();
	bool operator!=(const _Spliter_Iterator&);
	const char* operator*();
private:
	const Spliter& parent;
	int pos;
	char* buffer;
};
