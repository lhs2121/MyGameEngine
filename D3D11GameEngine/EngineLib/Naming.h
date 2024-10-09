#pragma once

struct NameObject
{
	base::string GetName()
	{
		base::string newName = name;
		newName += "_";
		char* buffer2 = new char[5];
		sprintf_s(buffer2, 5, "%d", count);

		if (count >= 100)
		{
		}
		else if (count >= 10)
		{
			char* buffer = new char[2];
			sprintf_s(buffer,2, "%d", 0);

			newName += buffer;
			delete[] buffer;
		}
		else
		{
			char* buffer = new char[3];
			sprintf_s(buffer,3, "%d%d", 0,0);

			newName += buffer;
			delete[] buffer;
		}
		newName += buffer2;
		
		delete[] buffer2;
		count++;
		return newName;
	}

	const char* name;
	UINT count;
};
class Naming
{
public:
	static void Create();
	static void Delete();

	static void AddName(const char* _name)
	{
		if (mainNaming->allNameObject.find(_name) != mainNaming->allNameObject.end())
		{
			return;
		}

		NameObject* newNameObject = new NameObject();
		newNameObject->name = _name;
		newNameObject->count = 0;

		mainNaming->allNameObject.insert({ _name,newNameObject });
	}

	static base::string GetName(const char* _name)
	{
		if (mainNaming->allNameObject.find(_name) == mainNaming->allNameObject.end())
		{
			Debug::MsgBoxAssert("해당 이름이 없습니다.");
		}
		
		return mainNaming->allNameObject[_name]->GetName();
	}

private:
	static Naming* mainNaming;
	~Naming()
	{
		for (auto& pair : mainNaming->allNameObject)
		{
			delete pair.second;
		}
		mainNaming->allNameObject.clear();
	}
	std::unordered_map<const char*, NameObject*> allNameObject;
};