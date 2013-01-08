#ifndef RENDER_ORDER_H
#define RENDER_ORDER_H


#include "GlobalList.h"


class Entity;


class RenderOrderItem
{
public:

	RenderOrderItem(Entity* parent)
	:_parent(parent)
	{
	}


	virtual ~RenderOrderItem()
	{
	}


	Entity* GetEntity()
	{
		return this->_parent;
	}

private:
	
	Entity*	_parent;

};


class BackgroundEntity : public GlobalList<BackgroundEntity>, public RenderOrderItem
{
public:

	BackgroundEntity(Entity* parent)
	:RenderOrderItem(parent)
	{
	}


	virtual ~BackgroundEntity()
	{
	}

};
typedef BackgroundEntity::GlobalList<BackgroundEntity> GlobalBackgroundEntityList;


class MidgroundEntity : public GlobalList<MidgroundEntity>, public RenderOrderItem
{
public:

	MidgroundEntity(Entity* parent)
	:RenderOrderItem(parent)
	{
	}


	virtual ~MidgroundEntity()
	{
	}

};
typedef MidgroundEntity::GlobalList<MidgroundEntity> GlobalMidgroundEntityList;


class ForegroundEntity : public GlobalList<ForegroundEntity>, public RenderOrderItem
{
public:

	ForegroundEntity(Entity* parent)
	:RenderOrderItem(parent)
	{
	}


	virtual ~ForegroundEntity()
	{
	}

};
typedef ForegroundEntity::GlobalList<ForegroundEntity> GlobalForegroundEntityList;


#endif