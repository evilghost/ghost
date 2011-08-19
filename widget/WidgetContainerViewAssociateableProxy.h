
#ifndef WIDGET_CONTAINER_VIEW_ASSOCIATEABLE_PROXY_H
#define WIDGET_CONTAINER_VIEW_ASSOCIATEABLE_PROXY_H

#include "../utility/Utility.h"

namespace ghost{

	namespace widget{

		class Container;
		class View;
		namespace view_proxy{
			class ContainerAssociateable;
		} // namespace view_proxy

		namespace container_proxy{

			class ViewAssociateable
				: private utility::NoCopyable
				, public utility::AssociateableProxy<Container>
			{
			protected:
				view_proxy::ContainerAssociateable* m_pViewProxy;

			public:
				explicit ViewAssociateable(Container& container);
				virtual ~ViewAssociateable();

			public:
				View* GetRootView() const;

			public: // 实现Associateable
				virtual bool AllowAssociatingWidth(Associateable* pObj) const;
				virtual void DisassociateFromAll();

			private: // 实现Associateable
				virtual bool IsAssociatedWidth(Associateable* pObj) const;
				virtual void DoAssociateWith(Associateable* pObj);
				virtual void DoDisassociateFrom(Associateable* pObj);
			};

		} // namespace container_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_VIEW_ASSOCIATEABLE_PROXY_H