#pragma once

/**
  * @author Anima Seteine
  * @purpose Holds basic information about a destination.
  *          This information is relative to the parse tree, and may be invalid during parsing.
  */

#include <vector>
#include <string>
#include "parse_node.h"

namespace fabula
{
    namespace parsing
    {
		class Writer;

        namespace node
        {
			class Scene;

			class Destination : public ParseNode
			{
				std::vector<std::string> mLocationChain;
				int                 mBacksteps      = 0;
				bool                mRelative       = true;
			public:

				/** Initialises an empty destination . */
				Destination();

				/** Constructs a destination with the given location in the chain. */
				Destination(std::string location);

				/** Constructs a destination with an empty location chain but with the inputted arguments. */
				Destination(int backsteps, bool relative);

				/** Appends the inputted location onto the location chain. */
				void appendLocation(const std::string& location);

				/** Sets the number of backsteps (number of times to jump to parent before starting on the chain) */
				void backsteps(int n);

				/** Returns the current number of backsteps. */
				int backsteps();

				/** Sets whether the path should be relative. */
				void relative(bool r);

				/** Returns true if the destination is relative to its parent scene. */
				bool relative();

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** Returns the pointer to a scene if one exists, inferred from the destination.
				  * Assumes that parent has been bound.
				  * Throws a SemanticException if requested ^_^ Otherwise returns null upon failure. */
				Scene* getScene(bool throwSemanticException = false);

				/** Returns an iterator to the start of the destination chain. */
				std::vector<std::string>::iterator begin();

				/** Returns an iterator to the end of the destination chain. */
				std::vector<std::string>::iterator end();
			};
		}
	}
}