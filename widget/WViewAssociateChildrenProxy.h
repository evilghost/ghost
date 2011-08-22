
#ifndef WIDGET_CONTAINER_ASSOCIATE_CHILDREN_PROXY_H
#define WIDGET_CONTAINER_ASSOCIATE_CHILDREN_PROXY_H

#include "../utility/Utility.h"
#include "WView.h"
#include "WViewAssociateParentProxy.h"
#include <list>

namespace ghost{

	namespace widget{

		namespace view_proxy{

			class AssociateChildren
				: private utility::NoCopyable
				, public utility::AssociateableProxy<View>
			{
			public:
				typedef std::list<view_proxy::AssociateParent*> ChildrenContainer;
			private:
				ChildrenContainer* m_pChildren;

			public:
				explicit AssociateChildren(View& view);
				virtual ~AssociateChildren();

			public: // 实现Associateable
				virtual bool AllowAssociatingWidth(Associateable* pObj) const;
				virtual void DisassociateFromAll();

			protected: // 实现Associateable
				virtual bool IsAssociatedWidth(Associateable* pObj) const;
				virtual void DoAssociateWith(Associateable* pObj);
				virtual void DoDisassociateFrom(Associateable* pObj);
			};

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_ASSOCIATE_CHILDREN_PROXY_H