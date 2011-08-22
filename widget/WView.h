
#ifndef WIDGET_VIEW_H
#define WIDGET_VIEW_H

#include "../utility/Utility.h"


namespace ghost{

	namespace widget{

		class Container;
		namespace view_proxy{
			class AssociateContainer;
			class AssociateParent;
			class AssociateChildren;
		} // namespace view_proxy

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
			view_proxy::AssociateContainer* m_pAssociateContainer;
			view_proxy::AssociateParent* m_pAssociateParent;
			view_proxy::AssociateChildren* m_pAssociateChildren;

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
			view_proxy::AssociateContainer* GetAssociateContainerProxy()
			{
				return m_pAssociateContainer;
			}
			view_proxy::AssociateParent* GetAssociateParentProxy()
			{
				return m_pAssociateParent;
			}
			view_proxy::AssociateChildren* GetAssociateChildrenProxy()
			{
				return m_pAssociateChildren;
			}

		public:
			bool SetContainer(Container* pContainer);
			Container* GetContainer() const;

			bool SetParent(View* pParent);
			View* GetParent() const;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_VIEW_H