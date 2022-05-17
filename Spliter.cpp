#include "Spliter.h"
#include <utility>

extern"C"
{
#include "Node.h"
#include "List.h"
}

#include <cstring>

typedef struct base_offset
{
	size_t base;
	size_t offset;
}base_offset;

Spliter::Spliter(char separator, Flag flag)
	:str(nullptr),separator(separator),flag(flag),spliter(BasicList_alloc(0)),max_len(0){
}

Spliter::~Spliter()
{
	if (flag == copy)
		delete[] str;
	BasicList_free(spliter);
}

size_t Spliter::maxSize()
{
	return max_len;
}

void Spliter::setSpliterByte(char separator)
{
	this->separator = separator;
}

int Spliter::operator<<(const char* src)
{
	if(str && flag == copy)
		delete[] str;
	BasicList_clear(spliter);
	switch (flag)
	{
	case copy:
		str = new char[strlen(src) + +sizeof('\0')];
		strcpy((char*)str, src);
		break;
	case move:
		str = src;
		break;
	default:
		break;
	}
	
	base_offset tmp;
	Node* tmpNode = nullptr;
	tmp.base = 0;
	tmp.offset = 0;
	do
	{
		if (*src != separator)
			tmp.offset++;
		else
		{
			tmpNode = BasicList_add(spliter, 0, sizeof(base_offset));
			if (!tmpNode)
				return 0;
			Node_getData(base_offset, tmpNode) = tmp;
			tmp.base += tmp.offset + sizeof(separator);
			max_len = max_len > tmp.offset ? max_len : tmp.offset;
			tmp.offset = 0;
		}
	} while (*(++src));
	tmpNode = BasicList_add(spliter, 0, sizeof(base_offset));
	if (!tmpNode)
		return 0;
	Node_getData(base_offset, tmpNode) = tmp;
	return spliter->length;
}


Spliter_group Spliter::operator[](int pos) const
{
	if (pos >= spliter->length)
		throw "Overflow";
	return Spliter_group(this,pos);
}

Spliter_group::Spliter_group(const Spliter* parent, int pos):parent(*parent),str(nullptr),sz(0),pos(pos)
{
	base_offset tmp = Node_getData(base_offset, BasicList_get(parent->spliter, pos));
	str = tmp.base + parent->str;
	sz = tmp.offset;
}

char* Spliter_group::operator>>(char* buffer)
{
	memcpy(buffer, str, sz);
	buffer[sz] = 0;
	return buffer;
}


_Spliter_Iterator::_Spliter_Iterator(const Spliter& parent,int pos):parent(parent),pos(pos),buffer(nullptr)
{
	buffer = new char[parent.max_len + sizeof('\0')];
}

_Spliter_Iterator::_Spliter_Iterator(const Spliter& parent, int pos,char* buffer) : parent(parent), pos(pos), buffer(buffer)
{
}

_Spliter_Iterator::_Spliter_Iterator(const _Spliter_Iterator& copy) : parent(copy.parent), pos(copy.pos), buffer(nullptr)
{
}

_Spliter_Iterator::_Spliter_Iterator(_Spliter_Iterator&& mv):parent(mv.parent),pos(mv.pos),buffer(mv.buffer)
{
	mv.buffer = nullptr;
}

_Spliter_Iterator::~_Spliter_Iterator()
{
	if(buffer)
		delete[] buffer;
}

_Spliter_Iterator _Spliter_Iterator::begin()
{
	return 	_Spliter_Iterator(std::move(*this));
}

_Spliter_Iterator _Spliter_Iterator::end()
{
	return 	_Spliter_Iterator(parent, parent.spliter->length,nullptr);
}

_Spliter_Iterator& _Spliter_Iterator::operator++()
{
	this->pos++;
	return *this;
}

bool _Spliter_Iterator::operator!=(const _Spliter_Iterator& cmp)
{
	return pos != cmp.pos;
}

const char* _Spliter_Iterator::operator*()
{
	return parent[pos] >> buffer;
}
