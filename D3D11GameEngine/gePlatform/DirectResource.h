#pragma once

class DirectResource
{
public:
	// constrcuter destructer
	DirectResource();
	virtual ~DirectResource();

	// delete Function
	DirectResource(const DirectResource& _Other) = delete;
	DirectResource(DirectResource&& _Other) noexcept = delete;
	DirectResource& operator=(const DirectResource& _Other) = delete;
	DirectResource& operator=(DirectResource&& _Other) noexcept = delete;

};