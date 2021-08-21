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
		WindowView(const sf::View& view, const sf::View& master);
		/**
		* Grabs the window.
		*/
		void grabWindow();
		/**
		* Releases the window.
		*/
		void releaseWindow();

		void moveViewChange(const sf::Vector2i& change);
		/**
		* Information about window grab status.
		* @return : true grabbed, false otherwise
		*/
		bool isGrabbed() const;
		/**
		* Sets a new connection with a window.
		* @return : true if a custom view is enabled for the window, false otherwise.
		*/
		bool customView() const;
		/**
		* Outputs the view parameter.
		* @return : const sf::View&
		*/
		const sf::View& getView() const;
		/**
		* Sets the view parameter.
		* @param[in] : const sf::View&
		*/
		void setView(const sf::View& view);
		/**
		* Moves the view.
		*/
		virtual void moveView(sf::RenderWindow& Window);
		/**
		* Outputs the view parameter of a main app.
		* @param[in] : const sf::View&
		*/
		const sf::View& getMasterView() const;
	};
}


#endif