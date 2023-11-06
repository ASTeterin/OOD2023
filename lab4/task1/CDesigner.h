#pragma once
#include "CPictureDraft.h"
#include "IShapeFactory.h"
#include <iostream>

class CDesigner
{
public:
	CDesigner(IShapeFactoryPtr&& shapeFactory)
		: m_shapeFactory(std::move(shapeFactory))
	{
	}
	CPictureDraft CreateDraft(std::istream& strm);

private:
	IShapeFactoryPtr m_shapeFactory;
};
