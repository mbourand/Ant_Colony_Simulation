#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include "Ant.hpp"

enum class ExplorerState
{
	EXPLORE, RETURN
};

class Explorer : public Ant
{

	private:
		ExplorerState state;

	public:
		Explorer();
		Explorer(const Explorer& Explorer);
		~Explorer();

		void operator=(const Explorer& other);

		ExplorerState getState() const;
		void setState(const ExplorerState state);

		void update();
};

#endif