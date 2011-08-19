
#ifndef WIDGET_CONTAINER_H
#define WIDGET_CONTAINER_H

#include "../utility/Utility.h"
#include "WidgetContainerViewAssociateableProxy.h"

namespace ghost{

	namespace widget{

		class View;

		/**
		* widget容器，连接widget系统与平台GUI系统
		* 容器维护一个唯一的View树，平台产生的事件将通过容器派发到此View树
		* 不允许C++语法上的拷贝，但允许通过Clone接口进行克隆（可只克隆容器本身，也可连同View树一同克隆）
		* 克隆不能克隆容器与平台GUI之间的关联，所以将丢失与平台GUI相关的一些状态或属性
		*/
		class Container 
			: private utility::NoCopyable
			, public utility::Cloneable{
		protected:
			container_proxy::ViewAssociateable m_viewAssociateable;

		protected:
			Container();

		public:
			virtual ~Container();

		public: // 实现Clonable
			virtual Container* Clone();
			enum CloneParam{
				WITH_VIEWS
			};
			template<CloneParam p>
			Container* Clone();

		public: // 获取代理对象
			container_proxy::ViewAssociateable& GetViewAssociateableProxy()
			{
				return m_viewAssociateable;
			}

		public:
			bool SetRootView(View* pView);
			View* GetRootView() const;

		public:
			virtual bool Invalidate(bool immediately = false) = 0;
			virtual bool Invalidate(Rect rect, bool immediately = false) = 0;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_H