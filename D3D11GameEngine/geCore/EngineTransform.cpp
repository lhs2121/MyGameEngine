#include "Pre.h"
#include "EngineTransform.h"

EngineTransform::EngineTransform()
{
}

EngineTransform::~EngineTransform()
{
}

void EngineTransform::TransformUpdate()
{
	ScaleMat.Scale(Scale);
	RotationMat.Rotation(Rotation);
	PositionMat.Position(Position);
	if (ChildTransform != nullptr)
	{

	}
}
