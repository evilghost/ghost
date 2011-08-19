
#ifndef WIDGET_CONTAINER_CONTAINER_ASSOCIATEABLE_PROXY_H
#define WIDGET_CONTAINER_CONTAINER_ASSOCIATEABLE_PROXY_H

#include "../utility/Utility.h"

namespace ghost{

	namespace widget{

		class View;
		class Container;
		namespace container_proxy{
			class ViewAssociateable;
		} // namespace container_proxy

		namespace view_proxy{

			class ContainerAssociateable
				: private utility::NoCopyable
				, public utility::AssociateableProxy<View>
			{
			protected:
				container_proxy::ViewAssociateable* m_pContainerProxy;

			public:
				explicit ContainerAssociateable(View& view);
				virtual ~ContainerAssociateable();

			public:
				Container* GetContainer() const;

			public: // 实现Associateable
				virtual bool AllowAssociatingWidth(Associateable* pObj) const;
				virtual void DisassociateFromAll();

			private: // 实现Associateable
				virtual bool IsAssociatedWidth(Associateable* pObj) const;
				virtual void DoAssociateWith(Associateable* pObj);
				virtual void DoDisassociateFrom(Associateable* pObj);
			};

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_CONTAINER_ASSOCIATEABLE_PROXY_H