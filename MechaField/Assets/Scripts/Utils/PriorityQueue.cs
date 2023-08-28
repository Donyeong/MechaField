using System.Collections;
using System.Collections.Generic;
using UnityEngine;


class PriorityQueueItem<T>
{
    public T Value { get; set; }
    public float Priority { get; set; }
}
class PriorityQueue<T>
{
    private List<PriorityQueueItem<T>> _heap = new List<PriorityQueueItem<T>>();

    public int Count
    {
        get
        {
            return this._heap.Count;
        }
    }

    public void Enqueue(float priority, T value)
    {
        _heap.Add(new PriorityQueueItem<T>() { Priority = priority, Value = value });

        int now = _heap.Count - 1;

        while (now > 0)
        {
            int next = (now - 1) / 2;

            if (_heap[now].Priority < _heap[next].Priority)
                break;

            PriorityQueueItem<T> temp = _heap[now];
            _heap[now] = _heap[next];
            _heap[next] = temp;
            now = next;
        }
    }

    public PriorityQueueItem<T> Dequeue()
    {
        PriorityQueueItem<T> ret = _heap[0];
        int lastIdx = _heap.Count - 1;

        _heap[0] = _heap[lastIdx];
        _heap.RemoveAt(lastIdx);
        lastIdx--;

        int now = 0;
        while (true)
        {
            int left = 2 * now + 1;
            int right = 2 * now + 2;

            int next = now;

            if (left <= lastIdx && _heap[next].Priority < _heap[left].Priority)
                next = left;
            if (right <= lastIdx && _heap[next].Priority < _heap[right].Priority)
                next = right;

            if (now == next)
                break;

            PriorityQueueItem<T> temp = _heap[now];
            _heap[now] = _heap[next];
            _heap[next] = temp;
            now = next;
        }

        return ret;
    }

}