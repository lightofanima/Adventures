import java.util.ArrayList;

public class Section
{
	ArrayList<Section> mNestedSections = new ArrayList<Section>();
	ArrayList<Scene>   mScenes         = new ArrayList<Scene>();
	Section			   mParent         = null;
	String mName = null;
	SectionLocation mCurrentLocation = null;

	
	Section(String name, Section parent)
	{
		mParent = parent;
		mName = name;
	}

	void addSection(Section section)
	{
		mNestedSections.add(section);
	}

	void addScene(Scene scene)
	{
		mScenes.add(scene);
	}

	Section findSectionInSection(String name)
	{
		for (int i = 0; i < mNestedSections.size(); ++i)
			if (mNestedSections.get(i).mName.equals(name))
				return mNestedSections.get(i);
		return null;
	}


	Scene findSceneInSection(String name)
	{
		for (int i = 0; i < mScenes.size(); ++i)
			if (mScenes.get(i).getName().equals(name))
				return mScenes.get(i);
		return null;
	}

	String getName()
	{
		return mName;
	}
	
	boolean isBase()
	{
		return this.getName().equals("base");
	}
	
	
//	SectionLocation getLocation()
//	{
//		if (mCurrentLocation==null)
//		{
//			SectionLocation location = new SectionLocation();
//			Section current = this;
//			
//			do
//			{
//				location.addLocation(current.getName());
//			} while ((current = current.mParent) != null && !current.isBase());
//			
//			mCurrentLocation = location;
//			return location;
//		}
//		else
//		{
//			return mCurrentLocation;
//		}
//	}

}