package text;

import static org.junit.Assert.*;

import org.junit.Test;

public class textTest {
	public text a;
	
	@Test
	public void testGet_a() {
		a.set_a(10);
		assertEquals(10,a.get_a());
	}

	@Test
	public void testGet_b() {
		a.set_b(1);
		assertEquals(1,a.get_b());
	}

}
