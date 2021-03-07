#ifndef MEP_WINDOW_VIEW_H
#define MEP_WINDOW_VIEW_H

#include <MEPGraphics/MEPGraphics.h>
namespace MEP {
	class WindowView {
	protected:
		//window movement
		sf::Vector2i m_windowPossChange;
		bool m_grabbedWindow = false;
		//custom view
		sf::View m_view;
		//view of a master window
		const sf::View* m_appView = nullptr;
		bool isCustomViewEnabled = false;
	public:
		WindowView() = default;
		/**
		* Enables WindowView class.
		*/
		WindowView(const sf::View& view, const sf::View& master) :
			m_view(view),
			m_appView(&master),
			isCustomViewEnabled(true) {}
		void grabWindow() {
			m_grabbedWindow = true;
		}
		void releaseWindow() {
			m_grabbedWindow = false;
		}
		void moveViewChange(const sf::Vector2i& change) {
			m_windowPossChange = change;
		}
		bool isGrabbed() const {
			return m_grabbedWindow;
		}
		/**
		* Sets a new connection with a window.
		* @return : true if a custom view is enabled for the window, false otherwise.
		*/
		bool customView() const {
			return isCustomViewEnabled and m_appView;
		}
		/**
		* Outputs the view parameter.
		* @return : const sf::View&
		*/
		const sf::View& getView() const {
			return m_view;
		}
		/**
		* Sets the view parameter.
		* @param[in] : const sf::View&
		*/
		void setView(const sf::View& view) {
			m_view = view;
		}
		/**
		* Moves the view.
		*/
		virtual void moveView(sf::RenderWindow& Window) {
			m_view.move(-(sf::Mouse::getPosition(Window).x - m_windowPossChange.x),
				-(sf::Mouse::getPosition(Window).y - m_windowPossChange.y));
			m_windowPossChange = sf::Mouse::getPosition(Window);
		}
		/**
		* Outputs the view parameter of a main app.
		* @param[in] : const sf::View&
		*/
		const sf::View& getMasterView() const {
			return *m_appView;
		}
	};
}


#endif