

public interface IGameCommand : IObjectPoolable
{
	public void Excute();
	public void ReturnObjectPool();
}