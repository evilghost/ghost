
#ifndef WIDGET_VIEW_H
#define WIDGET_VIEW_H

#include "../utility/Utility.h"
#include "WidgetViewContainerAssociateableProxy.h"

namespace ghost{

	namespace widget{

		class Container;

		/**
		* widget视图，每个widget组件的根基类
		* 每个View都是一颗树，View负责派发事件到此View的子View树
		* 不允许C++语法上的拷贝，但允许通过Clone接口进行克隆（可只克隆View本身，也可连同子View树一同克隆）
		* 克隆不能克隆View与平台GUI之间的关联，所以将丢失与平台GUI相关的一些状态或属性
		* 同时还会丢失其父view和Container相关的一些状态和属性
		*/
		class View 
			: private utility::NoCopyable
			, public utility::Cloneable{
		protected:
			view_proxy::ContainerAssociateable m_containerAssociateable;

		public:
			View();
			virtual ~View();

		public: // 实现Clonable
			virtual View* Clone();
			enum CloneParam{
				WITH_CHILDREN
			};
			template<CloneParam p>
			View* Clone();

		public: // 获取代理对象
			view_proxy::ContainerAssociateable& GetContainerAssociateableProxy()
			{
				return m_containerAssociateable;
			}

		public:
			bool SetContainer(Container* pContainer);
			Container* GetContainer() const;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_VIEW_H