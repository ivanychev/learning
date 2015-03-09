select JOB.job_id, 'CHICAGO:', isnull(chicago.quant, 0), 'BOSTON:', isnull(boston.quant, 0)
from
	JOB
	full join
	(
		(
		select job.job_id job_id, count(*) quant
		from JOB, EMPLOYEE, DEPARTMENT, LOCATION
		where	JOB.job_id = EMPLOYEE.job_id
		and		EMPLOYEE.department_id = DEPARTMENT.department_id
		and		DEPARTMENT.location_id = LOCATION.location_id
		and		LOCATION.regional_group = 'CHICAGO'
		group by job.job_id) as chicago

	full join

		(
		select job.job_id job_id, count(*) quant
		from JOB, EMPLOYEE, DEPARTMENT, LOCATION
		where	JOB.job_id = EMPLOYEE.job_id
		and		EMPLOYEE.department_id = DEPARTMENT.department_id
		and		DEPARTMENT.location_id = LOCATION.location_id
		and		LOCATION.regional_group = 'BOSTON'
		group by job.job_id) as boston
	
		on chicago.job_id = boston.job_id
	)
	on JOB.job_id = chicago.job_id
	or JOB.job_id = boston.job_id;