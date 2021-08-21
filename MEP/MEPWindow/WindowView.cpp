#include<MEPWindow/WindowView.h>

namespace MEP
{
	WindowView::WindowView(const sf::View& view, const sf::View& master) :
		m_view(view),
		m_appView(&master),
		isCustomViewEnabled(true) 
	{}

	void WindowView::grabWindow() 
	{
		m_grabbedWindow = true;
	}

	void WindowView::releaseWindow() 
	{
		m_grabbedWindow = false;
	}

	void WindowView::moveViewChange(const sf::Vector2i& change) 
	{
		m_windowPossChange = change;
	}

	bool WindowView::isGrabbed() const 
	{
		return m_grabbedWindow;
	}

	bool WindowView::customView() const 
	{
		return isCustomViewEnabled and m_appView;
	}

	const sf::View& WindowView::getView() const 
	{
		return m_view;
	}

	void WindowView::setView(const sf::View& view) 
	{
		m_view = view;
	}

	void WindowView::moveView(sf::RenderWindow& Window) 
	{
		m_view.move(-(sf::Mouse::getPosition(Window).x - m_windowPossChange.x),
			-(sf::Mouse::getPosition(Window).y - m_windowPossChange.y));
		m_windowPossChange = sf::Mouse::getPosition(Window);
	}

	const sf::View& WindowView::getMasterView() const 
	{
		return *m_appView;
	}
}