#pragma once

/**
  * @author Anima Seteine
  * @purpose This class holds the information about a single choice option.
  */

#include "parse_node.h"

namespace fabula
{
    namespace parsing
    {
		class Writer;

        namespace node
        {
            class Header;
            class Destination;

            class Choice : public ParseNode
            {
                Header*      mHeader      = nullptr;
                Destination* mDestination = nullptr;
        	public:

        		/** Initialises a choice, taking ownership of the arguments. */
        		Choice(Header* header, Destination* destination);

                /** Destroys the choice, deleting the children. */
        		~Choice();

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Returns the internal header. */
				Header& header();

				/** Returns the internal destination. */
				Destination& destination();
            };
        }
    }
}