insert(head, key, val) {
	node = alloc(key, val);

	do {
		prev = search_prev(head, key);
		node->next = prev->next;
		oldnext = prev->next;
	} while (CAS(&(prev->next), oldnext, node) != oldnext);
}
