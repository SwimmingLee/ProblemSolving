# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:

        dummy = ListNode(None)
        dummy.next = head
        start = dummy
        for _ in range(left-1):
            start = start.next
        end = start.next
        tmp = start.next

        for _ in range(right - left):
            start.next, end.next = end.next, end.next.next
            tmp, tmp.next = start.next, tmp

        return dummy.next
