#include "request_queue.h"

#include <vector>
#include <string>

RequestQueue::RequestQueue(const SearchServer& search_server) 
: search_server_(search_server)
{
}
    
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    std::vector<Document> v = search_server_.FindTopDocuments(raw_query, status);
    QueryResult q;
    q.is_doc = v.size() > 0;
    requests_.push_back(q);
    CheckRequest();
    return v;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    std::vector<Document> v = search_server_.FindTopDocuments(raw_query);
    requests_.push_back({!v.empty()});
    CheckRequest();
    return v;
}

int RequestQueue::GetNoResultRequests() const {
    return count_if(requests_.begin(), requests_.end(), [] (const QueryResult& q) {
        return q.is_doc == false;
    });
}
    
void RequestQueue::CheckRequest() {
    if (requests_.size() > min_in_day_) {
        requests_.pop_front();
    }
}