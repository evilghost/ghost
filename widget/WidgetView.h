
#ifndef WIDGET_VIEW_H
#define WIDGET_VIEW_H

#include "../utility/Utility.h"
#include "WidgetViewContainerAssociateableProxy.h"

namespace ghost{

	namespace widget{

		class Container;

		/**
		* widget��ͼ��ÿ��widget����ĸ�����
		* ÿ��View����һ������View�����ɷ��¼�����View����View��
		* ������C++�﷨�ϵĿ�����������ͨ��Clone�ӿڽ��п�¡����ֻ��¡View����Ҳ����ͬ��View��һͬ��¡��
		* ��¡���ܿ�¡View��ƽ̨GUI֮��Ĺ��������Խ���ʧ��ƽ̨GUI��ص�һЩ״̬������
		* ͬʱ���ᶪʧ�丸view��Container��ص�һЩ״̬������
		*/
		class View 
			: private utility::NoCopyable
			, public utility::Cloneable{
		protected:
			view_proxy::ContainerAssociateable m_containerAssociateable;

		public:
			View();
			virtual ~View();

		public: // ʵ��Clonable
			virtual View* Clone();
			enum CloneParam{
				WITH_CHILDREN
			};
			template<CloneParam p>
			View* Clone();

		public: // ��ȡ�������
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