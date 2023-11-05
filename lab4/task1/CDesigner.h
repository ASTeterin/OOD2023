#pragma once
#include "CPictureDraft.h"
#include "IDesigner.h"
#include "IShapeFactory.h"
#include <iostream>

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactoryPtr&& shapeFactory)
		: m_shapeFactory(std::move(shapeFactory))
	{
	}
	CPictureDraft CreateDraft(std::istream& strm) override;

private:
	IShapeFactoryPtr m_shapeFactory;
};
