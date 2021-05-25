# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:

        start = head
        for _ in range(left-1):
            start = start.next
        end = start.next

        for _ in range(right - left):
            end.next, end = end, end.next.next
