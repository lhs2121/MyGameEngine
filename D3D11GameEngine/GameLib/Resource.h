#pragma once
#include <type_traits>

class Resource
{
public:
	template<class T>
	static T* Load(const char* _path)
	{
		if (std::is_same<T, ITexture>::value)
		{
			EngineDirectory dir;
			dir.GoChild("Assets");
			dir.GoChild(_path);
			EngineFile file = dir.GetFile();

			ITexture* tex = (ITexture*)mainResourceManager->CreateResource(ResType::Texture, file.GetFileName());
			tex->Setting(file);
			return tex;
		}
	}

	static IResManager* mainResourceManager;
};