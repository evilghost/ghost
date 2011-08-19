
#include "../widget/Widget.h"

class TestContainer : public ghost::widget::Container{
public:
	virtual bool Invalidate(bool immediately = false){return false;}
	virtual bool Invalidate(ghost::utility::Rect rect, bool immediately = false){return false;}
};

void Test()
{
	ghost::widget::View view;
	TestContainer container;
	view.SetContainer(&container);
}

int main()
{
	Test();
	return 0;
}