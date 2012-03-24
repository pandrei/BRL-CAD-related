long int rt_tor_surface_area(struct bu_vls *str, const struct rt_db_internal *ip, int verbose, double mm2local){
    register struct rt_tor_internal *tip =
	(struct rt_tor_internal *)ip->idb_ptr;
	double r3,r4,sArea;

	r3 = tip->r_a - tip->r_h;
	r4 = tip->r_a + tip->r_h;
	sArea = (bn_pi * bn_pi)*(r4+r3)*(r4-r3);
}
