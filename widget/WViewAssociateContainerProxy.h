
#ifndef WIDGET_CONTAINER_ASSOCIATE_CONTAINER_PROXY_H
#define WIDGET_CONTAINER_ASSOCIATE_CONTAINER_PROXY_H

#include "../utility/Utility.h"
#include "WView.h"
#include "WContainerAssociateViewProxy.h"

namespace ghost{

	namespace widget{

		class Container;

		namespace view_proxy{

			class AssociateContainer
				: public utility::SingleAssociateableProxy<View, container_proxy::AssociateView>
			{
			public:
				explicit AssociateContainer(View& view);
				virtual ~AssociateContainer();

			public:
				Container* GetContainer() const;

			protected: //  µœ÷Associateable
				virtual void DoAssociateWith(Associateable* pObj);
				virtual void DoDisassociateFrom(Associateable* pObj);
			};

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_ASSOCIATE_CONTAINER_PROXY_H