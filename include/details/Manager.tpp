/*
 * load will first see if the file is stored in the table.
 * If it is not, it will load it into the table, and then return
 * a reference to it.
 *
 * If the resource was in the table, a reference to that resource
 * is returned.
 */
template <typename T>
T & Manager<T>::load (const std::string & file)
{
    auto it { table.find (file) };
    if ( it == table.end () )
    {
        ptr<T> tmp { std::make_unique<T> () };
        if ( !tmp -> loadFromFile (file) )
	    throw Manager_Error { "Unable to load file '"s + file + "'" };
        it = table.insert (std::make_pair (file, std::move (tmp))).first;
    } 
    return *(it -> second);
}

/*
 * Sometimes, say if we have to load alot of resources, it might
 * be good to unload some unused resources. If we do not, we might
 * still get memory leaks (but hopefully not as quickly and frequently
 * as if we loaded these files manually in all places where we needed
 * them).
 */
template <typename T>
void Manager<T>::unload (const std::string & file)
{
    table.erase (table.find (file));
}

/*
 * Initialize the table to be empty at first.
 */
template <typename T>
std::unordered_map<std::string, ptr<T>> Manager<T>::table { };
