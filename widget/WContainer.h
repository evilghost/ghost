
#ifndef WIDGET_CONTAINER_H
#define WIDGET_CONTAINER_H

#include "../utility/Utility.h"

namespace ghost{

	namespace widget{

		class View;
		namespace container_proxy{
			class AssociateView;
		} // namespace container_proxy

		/**
		* widget����������widgetϵͳ��ƽ̨GUIϵͳ
		* ����ά��һ��Ψһ��View����ƽ̨�������¼���ͨ�������ɷ�����View��
		* ������C++�﷨�ϵĿ�����������ͨ��Clone�ӿڽ��п�¡����ֻ��¡��������Ҳ����ͬView��һͬ��¡��
		* ��¡���ܿ�¡������ƽ̨GUI֮��Ĺ��������Խ���ʧ��ƽ̨GUI��ص�һЩ״̬������
		*/
		class Container 
			: private utility::NoCopyable
			, public utility::Cloneable{
		protected:
			container_proxy::AssociateView* m_pAssociateView;

		protected:
			Container();

		public:
			virtual ~Container();

		public: // ʵ��Clonable
			virtual Container* Clone();
			enum CloneParam{
				WITH_VIEWS
			};
			template<CloneParam p>
			Container* Clone();

		public: // ��ȡ�������
			container_proxy::AssociateView* GetAssociateViewProxy()
			{
				return m_pAssociateView;
			}

		public:
			bool SetRootView(View* pView);
			View* GetRootView() const;

		public:
			virtual bool Invalidate(bool immediately = false) = 0;
			virtual bool Invalidate(utility::Rect rect, bool immediately = false) = 0;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_H