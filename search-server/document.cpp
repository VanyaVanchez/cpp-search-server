#include "document.h"

#include <iostream>
#include <string>


Document::Document() = default;

Document::Document(int id, double relevance, int rating)
        : id(id)
        , relevance(relevance)
        , rating(rating) {
}

std::ostream& operator<<(std::ostream& out, const Document& doc){
    out << "{ document_id = " << doc.id << ", relevance = " << doc.relevance << ", rating = " << doc.rating << " }";
    return out; 
}